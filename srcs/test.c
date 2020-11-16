#include "minishell.h"

void    proc_sigint_handler(int signo)
{
    if (g_shell.pid == 0 && g_shell.bool == 0)
    {
        write(1, "\n", 1);
        kill(0, signo);
        g_shell.pid = 1; // WTF
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
    int   bool;
    int   status;
    int   fd[2];

    fd[0] = 1;
	fd[1] = 1;
    bool = 0;
    status = 0;
    while (cmd) 
    {
        if (cmd->tokens[0])
        {
            if (ft_strcmp(cmd->tokens[0], "make") == 0)
                g_shell.bool = 1;
            pipe(p);
            pid = fork();
            signal(SIGINT, proc_sigint_handler);
            g_shell.pid = 0;
            if (pid == -1)
                exit(EXIT_FAILURE);
            else if (pid == 0)
            {
                g_shell.pid = 1;
                dup2(fd[0], 0); //change the input according to the old one 
                if (cmd->next)
                    dup2(p[1], 1);
                close(p[0]);
                execute(cmd, envp, fd, 0);
                exit(EXIT_SUCCESS);
            }
            else
            {
                execute(cmd, envp, fd, 1);
                wait(&status);
                close(p[1]);
                fd[0] = p[0]; //save the input for the next command
                if (cmd->next != NULL)
                    cmd = cmd->next;
                else
                    break;
            }
        }
        else
            cmd = cmd->next;
    }
}
