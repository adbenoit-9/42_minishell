/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 13:44:06 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_try_path(t_stock **cmd_lst, char *envp[], char *args[])
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;
	int		fd[2];

	if (ft_redirect(cmd_lst, &fd[0], &fd[1]) == -1)
		return (-1);
	if ((*cmd_lst)->sep == RIGHT)
		dup2(fd[0], 1);
	if ((*cmd_lst)->sep == LEFT || (*cmd_lst)->input)
		dup2(fd[1], 0);
	ret = find_var(envp, "PATH");
	path = ft_split(envp[ret], ':');
	i = 0;
	printf("path is : %s\n", path[0]);
	printf("path is : %s\n", path[1]);
	printf("path is : %s\n", path[2]);
	printf("path is : %s\n", path[3]);
	printf("path is : %s\n", path[4]);
	printf("path is : %s\n", path[5]);
	int y = 0;
	while (path[i] != 0)
	{
		y++;
		printf("y : %d\n\n", y);
		add_p = ft_strjoin(path[i], "/");
		new_p = ft_strjoin(add_p, args[0]);
		free(add_p);
		if (execve(new_p, args, envp) == -1)
		{
			free(new_p); //il faut free le bon
			i++;
			printf("i : %d\n\n", i);
		}
		else
		{
			printf("path[i] = %s\n", path[i]);
			return (1);}
	}
	return (0);
}

// int		ft_launch_process(t_stock **cmd_lst, char **args, char *envp[])
// {
// 	pid_t	pid;
// 	int		ret;
// 	int		status;

// 	pid = fork();
// 	ret = 0;

// 	if (pid == 0)
// 	{
// 		ret = ft_try_path(cmd_lst, envp, args);
// 		exit(0);
// 	}
// 	else if (pid < 0)
// 		return (ret);
// 	else
// 	{
// 		ret = 1;
// 		wait(&status);
// 	}
// 	return (ret);
// }

/*nt		ft_launch_process(t_stock **cmd_lst, char **args, char *envp[])
{
	pid_t	pid;
	int		ret;
	int		status;
	int		p[2];
	int		fd_in;

	pipe(p);
	pid = fork();
	ret = 0;
	fd_in = 0;

	if (pid == 0)
	{
		dup2(fd_in, 0);
		if ((*cmd_lst)->next != NULL)
			dup2(p[1], 1);
		close(p[0]);
		ret = ft_try_path(cmd_lst, envp, args);
		exit(0);
	}
	else if (pid < 0)
		exit (EXIT_FAILURE);
	else
	{
		ret = 1;
		wait(&status);
		close(p[1]);
		fd_in = p[0];
		//(*cmd_lst) = (*cmd_lst)->next;
	}
	return (ret);
}*/

void    loop_pipe(t_stock **cmd_lst, char **args, char *envp[]) 
{
	int  	p[2];
	int  	fd_in;
	int 	ret; 
	pid_t	pid;

	fd_in = 0;
	ret = 0;
	
	while (*cmd_lst != NULL)
	{
    	pipe(p);
    	if ((pid = fork()) == -1)
        	exit(EXIT_FAILURE);
		else if (pid == 0)
        {
			printf("AAAAAAAAAAAAAA\n");
        	dup2(fd_in, 0); //change the input according to the old one 
			printf("BBBBBBBBBBBBBB\n");
        	if ((*cmd_lst)->next != NULL)
        		dup2(p[1], 1);
        	close(p[0]);
			printf("CCCCCCCCCCCCCCC\n");
        	ret = ft_try_path(cmd_lst, envp, args);
			printf("RET is %d\n", ret);
        	exit(EXIT_FAILURE);
        }
    	else
    	{
        	wait(NULL);
        	close(p[1]);
        	fd_in = p[0]; //save the input for the next command
			if ((*cmd_lst)->next != NULL && (*cmd_lst)->sep == PIPE)
				(*cmd_lst) = (*cmd_lst)->next;
			else
				break;
        }
    }
}

/*int		ft_launch_process(t_stock **cmd_lst, char **args, char *envp[])
{
	int		fd_in;
	int		p[2];
	pid_t	pid;
	int		ret;

	fd_in = 0;
	ret = 0;
	while ((*cmd_lst)!= NULL)
	{
		pipe(p);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0);
			if ((*cmd_lst)->next != NULL)
				dup2(p[1], 1);
			close(p[0]);
			ret = ft_try_path(cmd_lst, envp, args);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0];
			(*cmd_lst) = (*cmd_lst)->next;
		}
		exit (EXIT_SUCCESS);
	}
	return (0);
}*/

void	ft_unknow(t_stock **cmd_lst, char *envp[])
{
	//int	ret;
	int	i;

	//ret = ft_launch_process(cmd_lst, (*cmd_lst)->tokens, envp);
	loop_pipe(cmd_lst, (*cmd_lst)->tokens, envp);
	i = 0;
	printf("YOLO\n\n");
	//printf("ret = %d\n", ret);
	/*if (ret == 0)
	{
		while ((*cmd_lst)->tokens[0][i] && (*cmd_lst)->tokens[0][i] != '/')
			++i;
		if ((size_t)i < ft_strlen((*cmd_lst)->tokens[0]))
			write_error("\0", (*cmd_lst)->tokens[0],
			": No such file or directory\n");
		else
			write_error("\0", (*cmd_lst)->tokens[0], ": command not found\n");
	}*/
}
