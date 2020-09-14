#include "minishell.h"

void    ft_unset(t_stock **cmd_lst, char *envp[])
{
    int     i;

    i = 0;
    while ((*cmd_lst)->input[i])
    {
        if ((*cmd_lst)->input[i] == '=')
        {
            (*cmd_lst)->output = output_error("unset: `", (*cmd_lst)->input, "': not a valid identifier\n");
            return ;
        }
        ++i;
    }
    i = find_var(envp, (*cmd_lst)->input); 
}
