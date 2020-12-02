#include "minishell.h"

void    proc_sig_handler(int signo)
{
    if (g_shell.pid == 0 && g_shell.bool == 1)
    {
        g_shell.pid = 1;
        g_shell.bool = 0;
    }
    else if (g_shell.pid == 0 && g_shell.bool == 0)
    {
        (void)signo;
        kill(0, signo);
        g_shell.sig = 1;
        g_shell.pid = 1;
    }
}

/*void    proc_sigquit_handler(int signo)
{
    if (g_shell.bool == 0)
    {
        write(1, "\n", 1);
        kill(0, signo);
        g_shell.pid = 1; // WTF
    }
}*/

/*
** ===> cmd = adresse d'un tableau, de tableaux de strings
** ===> (*cmd) = tableau de tableaux de string (ou premier élément du tableau
** donc )
** ===> (**cmd) = 
*/

void    ft_loop_pipe(t_stock *cmd, char *envp[]) 
{
    int   p[2];
    pid_t pid; 
    int   status;
    int   fd[2];

    fd[0] = 1;
	fd[1] = 1;
    while (cmd) 
    {
        status = 0;
        //signal(SIGINT, proc_sigint_handler);
        if (cmd->tokens[0] && ft_strcmp(cmd->tokens[0], "make") == 0)
            g_shell.bool = 1;
        if (cmd->tokens[0] && ft_strcmp(cmd->tokens[0], "exit") == 0)
        {
            g_shell.bool = 0;
            g_shell.pid = 1;
        }
        pipe(p);
        pid = fork();
        g_shell.sig = 0;
        signal(SIGINT, proc_sig_handler);
        signal(SIGQUIT, proc_sig_handler);
        g_shell.pid = 0;
        if (pid == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            g_shell.pid = 1;
            g_shell.bool = 0;
            dup2(fd[0], 0); //change the input according to the old one 
            if (cmd->next)
                dup2(p[1], 1);
            close(p[0]);
            execute(cmd, envp, fd, 0);
            //signal(SIGINT, proc_sigint_handler);
           // break ;
            exit(EXIT_SUCCESS);
        }
        else
        {
            execute(cmd, envp, fd, 1);
            waitpid(pid, &status, 0);
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
            if (cmd->next != NULL)
                cmd = cmd->next;
            else
                break ;
        }
    }
}
