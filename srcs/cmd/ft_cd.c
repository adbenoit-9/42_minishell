/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/27 17:41:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t  path_len(char *token)
{
    size_t  i;
    size_t  len;
    size_t  tmp;

    len = 0;
    i = 0;
    while (token && token[i])
    {
        ++len;
        tmp = i;
        while(token[tmp] == '/' && token[i + 1] == '/')
            ++i;
        ++i;
    }
    return (len);
}

void	modify_pwd(char *envp[], char *var)
{
	int		i;
	int		j;
	int		k;
	size_t	size;
	char	*str;
	char	*buf;

	size = 0;
	buf = NULL;
	str = getcwd(buf, size);
    i = find_var(envp, var);
    j = 0;
    while (envp[i][j] && envp[i][j] != '=')
        ++j;
	size += ft_strlen(var) + 1;
    if (ft_strlen(envp[i]) < size)
    {
        envp[i] = realloc(envp[i], size + 1);
    }
    k = -1;
    while (str[++k])
        envp[i][++j] = str[k];
    envp[i][j + 1] = 0;
}

void    ft_cd(t_stock **cmd_lst, char *envp[])
{
    int     ret;
    char    *str;
    char    *path;
    int     i;
    int     j;

    errno = 0;
    if (!(path = malloc(path_len((*cmd_lst)->tokens[0]) + 1)))
    {
        write_error("", strerror(errno), "\n", 1);
        return ;
    }
    i = 0;
    j = 0;
    while ((*cmd_lst)->tokens[0] && (*cmd_lst)->tokens[0][i])
    {
        path[j] = (*cmd_lst)->tokens[0][i];
        ++j;
        ret = i;
        while((*cmd_lst)->tokens[0][ret] == '/' && (*cmd_lst)->tokens[0][i + 1] == '/')
            ++i;
        ++i;
    }
    path[j] = 0;
    modify_pwd(envp, "OLDPWD");
    ret = chdir((const char *)path);
    if (ret == 0)
	{
		modify_pwd(envp, "PWD");
        erret = 0;
	}
    else
    {
        str = strerror(errno);
        write_error("cd: ", (*cmd_lst)->tokens[0], ": ", 1);
        write(1, str, ft_strlen(str));
        write(1, "\n" , 1);
    }
    free(path);
}