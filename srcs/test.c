#include "minishell.h"

/*
**
*/

void    ft_son(t_stock *cmd, int fd, int *p, char *envp[])
{
    g_shell.pid = 1;
    g_shell.bool = 0;
    dup2(fd, 0);
    if (cmd->next)
        dup2(p[1], 1);
    // close(p[0]);
    execute(cmd, envp, 0);
    // close(fd);
    exit(EXIT_SUCCESS);
}

/*
**
*/

void    ft_parent(t_stock *cmd, int fd, int *p, char *envp[], int status)
{
    execute(cmd, envp, 1);
    printf("fd = %d\n", fd);
    // close(fd);
    if (g_shell.sig == 1)
	{
        if (WIFSIGNALED(status) == 1)
        {
            write(1, "\n", 1);
			g_status = 130;
        }
        else
		    g_status = 255; 
	}
    else if (status % 255 != 0)
        g_status = status % 255;
    else if (status != 0)
        g_status = 255;
    // close(p[1]);
    fd = dup(p[0]);
}

/*
**
*/

void    ft_mana_sig(t_stock *cmd)
{
    if (cmd->tokens[0] && ft_strcmp(cmd->tokens[0], "make") == 0)
         g_shell.bool = 1;
    if (cmd->tokens[0] && ft_strcmp(cmd->tokens[0], "exit") == 0)
    {
        g_shell.bool = 0;
        g_shell.pid = 1;
    }
    g_shell.sig = 0;
    signal(SIGINT, proc_sig_handler);
    signal(SIGQUIT, proc_sig_handler);
    g_shell.pid = 0;
}

/*
**
*/


void    ft_loop_pipe(t_stock *cmd, char *envp[]) 
{
    int     p[2];
    int     fd_in;
    int     status;
    int     nb_wait;
    pid_t   pid; 

    status = 0;
    nb_wait = 0;
    fd_in = 0;
    while (cmd) 
    {
        ft_mana_sig(cmd);
        if (pipe(p) == -1)
        {
            printf("ERROR TO MANAGE\n");
            exit(EXIT_FAILURE);
        }
        if ((pid = fork()) == -1)
        {
            printf("ERROR TO MANAGE\n");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
            ft_son(cmd, fd_in, p, envp);
        else
        {
            ft_parent(cmd, fd_in, p, envp, status);
            if (cmd->next != NULL)
                cmd = cmd->next;
            else
                break ;
            nb_wait++;
        }
    }
    while(nb_wait-- >= 0)
        wait(&status);
}
