#include "minishell.h"

/*
** ===> cmd = adresse d'un tableau, de tableaux de strings
** ===> (*cmd) = tableau de tableaux de string (ou premier élément du tableau
** donc )
** ===> (**cmd) = 
*/

void    ft_loop_pipe(t_stock **cmd, char *envp[], int *fd) 
{
    int   p[2];
    pid_t pid;
    int   bool;
    
    fd[0] = 0;
    bool = 0;

    while (*cmd) 
    // && ((*cmd)->sep == PIPE && (*cmd)->next->tokens[0] != NULL))
      //      || (bool = 1 && (*cmd)->tokens[0] != NULL && (*cmd)->sep != PIPE))
    {
        pipe(p);
        if ((pid = fork()) == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            dup2(fd[0], 0); //change the input according to the old one 
            if ((*cmd)->next)
                dup2(p[1], 1);
            close(p[0]);
            ft_try_path(cmd, envp, (*cmd)->tokens, fd);
            //ft_launch_process(cmd, (*cmd)->tokens, envp);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            fd[0] = p[0]; //save the input for the next command
            if ((*cmd)->next != NULL)
                (*cmd) = (*cmd)->next;
            else
                break;
        }
    }
}