#include "minishell.h"

/*
**
*/

void    ft_son(t_stock *cmd, int *fd, int *p, char *envp[])
{
    g_shell.pid = 1;
    g_shell.bool = 0;
    dup2(fd[0], 0);
    if (cmd->next)
        dup2(p[1], 1);
    close(p[0]);
    execute(cmd, envp, fd, 0);
    exit(EXIT_SUCCESS);
}

/*
**
*/

void    ft_parent(t_stock *cmd, int *fd, int *p, char *envp[], int status)
{
    execute(cmd, envp, fd, 1);
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
    close(p[1]);
    fd[0] = p[0];
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
    int     fd[2];
    int     status;
    int     nb_wait;
    pid_t   pid; 

    status = 0;
    nb_wait = 0;
    fd[0] = 1;
	fd[1] = 1;
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
            ft_son(cmd, fd, p, envp);
        else
        {
            ft_parent(cmd, fd, p, envp, status);
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
