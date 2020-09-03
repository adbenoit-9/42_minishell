#include "minishell.h"

void    ft_unset(t_stock **cmd_lst, char *envp[])
{
    (void)envp;
    (*cmd_lst)->ret = 0;
}
