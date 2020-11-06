/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 00:21:17 by adbenoit         ###   ########.fr       */
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

void	modify_pwd(char *str, char *envp[], char *var)
{
	int		i;
	int		j;
	int		k;
	size_t	size;

	size = 0;
    if (!str)
	    str = getcwd(NULL, size);
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
    free(str);
}

void    ft_cd(t_stock **cmd, char *envp[])
{
    int     ret;
    char    *str;
    char    *path;
    int     i;
    int     j;

    errno = 0;
    if (!(path = malloc(path_len((*cmd)->tokens[1]) + 1)))
    {
        write_error("", strerror(errno), "\n", 1);
        return ;
    }
    i = 0;
    j = 0;
    while ((*cmd)->tokens[1] && (*cmd)->tokens[1][i])
    {
        path[j] = (*cmd)->tokens[1][i];
        ++j;
        ret = i;
        while((*cmd)->tokens[1][ret] == '/' && (*cmd)->tokens[1][i + 1] == '/')
            ++i;
        ++i;
    }
    path[j] = 0;
    str = getcwd(NULL, 0);
    ret = chdir((const char *)path);
    if (ret == 0)
	{
        modify_pwd(str, envp, "OLDPWD");
		modify_pwd(NULL, envp, "PWD");
        g_status = 0;
	}
    else
    {
        free(str);
        str = strerror(errno);
        write_error("cd: ", (*cmd)->tokens[1], ": ", 1);
        write(1, str, ft_strlen(str));
        write(1, "\n" , 1);
    }
    free(path);
}