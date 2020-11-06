#include "minishell.h"

/*
** ===> cmd = adresse d'un tableau, de tableaux de strings
** ===> (*cmd) = tableau de tableaux de string (ou premier élément du tableau
** donc )
** ===> (**cmd) = 
*/

void    ft_loop_pipe(t_stock **g_cmd, char *envp[]) 
{
    int   p[2];
    pid_t pid; 
    int   fd_in;
    int   bool;
    
    fd_in = 0;
    bool = 0;

    while (*g_cmd) 
    // && ((*g_cmd)->sep == PIPE && (*g_cmd)->next->tokens[0] != NULL))
      //      || (bool = 1 && (*g_cmd)->tokens[0] != NULL && (*g_cmd)->sep != PIPE))
    {
        pipe(p);
        if ((pid = fork()) == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            dup2(fd_in, 0); //change the input according to the old one 
            if ((*g_cmd)->next)
                dup2(p[1], 1);
            close(p[0]);
            ft_try_path(g_cmd, envp, (*g_cmd)->tokens);
            //ft_launch_process(g_cmd, (*g_cmd)->tokens, envp);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            fd_in = p[0]; //save the input for the next command
            if ((*g_cmd)->next != NULL)
                (*g_cmd) = (*g_cmd)->next;
            else
                break;
        }
    }
}