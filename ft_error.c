#include "minishell.h"

int    ft_error(t_list *order)
{
    free(order);
    return (0);
}