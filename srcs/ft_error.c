#include "minishell.h"

int    ft_error(t_stock *cmd_lst)
{
    free(cmd_lst);
    return (0);
}