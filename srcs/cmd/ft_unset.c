#include "minishell.h"

void    ft_unset(t_stock **cmd_lst, char *envp[])
{
    int     i;
    char    *str;
    char    *new;

    i = 0;
    while ((*cmd_lst)->input[i])
    {
        if ((*cmd_lst)->input[i] == '=')
        {
            str = strdup("unset: ");
            new = ft_strjoin(str, (*cmd_lst)->input);
            free(str);
            str = ft_strjoin(new, ": not a valid identifier\n");
            free(new);
            (*cmd_lst)->output = str;
            return ;
        }
        ++i;
    }
    i = find_var(envp, (*cmd_lst)->input); 
}
