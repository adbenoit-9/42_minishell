#include "minishell.h"

/*
** ===> cmd = adresse d'un tableau, de tableaux de strings
** ===> (*cmd) = tableau de tableaux de string (ou premier élément du tableau
** donc )
** ===> (**cmd) = 
*/

void    ft_loop_pipe(t_stock **cmd_lst, char *envp[]) 
{
    int   p[2];
    pid_t pid; 
    int   fd_in;
    int   bool;
    
    fd_in = 0;
    bool = 0;

    while (*cmd_lst) 
    // && ((*cmd_lst)->sep == PIPE && (*cmd_lst)->next->tokens[0] != NULL))
      //      || (bool = 1 && (*cmd_lst)->tokens[0] != NULL && (*cmd_lst)->sep != PIPE))
    {
        pipe(p);
        if ((pid = fork()) == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            dup2(fd_in, 0); //change the input according to the old one 
            if ((*cmd_lst)->next)
                dup2(p[1], 1);
            close(p[0]);
            printf("here ??\n");
            ft_try_path(cmd_lst, envp, (*cmd_lst)->tokens);
            printf("WTF\n");
            //ft_launch_process(cmd_lst, (*cmd_lst)->tokens, envp);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            fd_in = p[0]; //save the input for the next command
            if ((*cmd_lst)->next != NULL)
                (*cmd_lst) = (*cmd_lst)->next;
            else
                break;
        }
    }
}