/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:13:08 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/29 22:39:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_try_path(char *envp[], char *args[])
{
	int		ret;
	int		i;
	char	**path;
	char 	*add_p;
	char	*new_p;

	ret = find_var(envp, "PATH");
	path = ft_split(envp[ret], ':');
	i = 0;
	while (path[i] != '\0')
	{
		add_p = ft_strjoin(path[i], "/");
		new_p = ft_strjoin(add_p, args[0]);
		free(add_p);
		if (execve(new_p, args + 1, envp) == -1)
		{
			free(new_p); // faudra free celui qui marche à la fin du coup
			i++;
		}
		else
			return (1) ;
	}
	return (0);
}

int		ft_launch_process(char *cmd, char *envp[])
{
	pid_t	pid;
	int		ret;
	int		status;
	char	**args;

	pid = fork();
	ret = 0;
	args = ft_split(cmd, ' ');
	if (pid == 0)
		ret = ft_try_path(envp, args);
	else if (pid < 0)
		return (ret);
	else
	{
		ret = 1;
		wait(&status);
	}
	return (ret);
}

int    execute(t_stock **cmd_lst, char *envp[])
{
    t_function	cmd_fct[NUM_CMD] = {ft_echo, ft_cd, ft_pwd, ft_env,
									ft_export, ft_unset, ft_exit};
    int			i;
	int			ret;

    i = 0;
    while (*cmd_lst && i < NUM_CMD && (*cmd_lst)->cmd != i)
        ++i;
	if (*cmd_lst == 0)
		return (0);
    if (*cmd_lst && (*cmd_lst)->cmd != UNKNOW)
        cmd_fct[i](cmd_lst, envp);
	else if ((*cmd_lst)->cmd == UNKNOW)
	{
		if ((ret = ft_launch_process((*cmd_lst)->input, envp)) == 0)
			(*cmd_lst)->output = output_error("\0", (*cmd_lst)->input, ": command not found\n");
	}
	launch_cmd(cmd_lst, envp);
	return (0);
}
