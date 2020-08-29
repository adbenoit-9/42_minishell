#include "minishell.h"

void    ft_unset(t_list **cmd_lst)
{
    (*cmd_lst)->ret = 0;
}
