/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:35:32 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/03 22:31:53 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define ECHO 0
#define ECHO_N 8
#define CD 1
#define PWD 2
#define ENV 3
#define EXPORT 4
#define UNSET 5
#define EXIT 6
#define UNKNOW 7
#define ERROR 9
#define NUM_CMD 7

#define NONE -1
#define PIPE 0
#define COMA 1
#define RIGHT 2
#define LEFT 3
#define D_RIGHT 4
#define D_LEFT 5
#define AND 6
#define OR 7
#define NUM_SEP 8

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_list
{
	char			*input;
	char			*output;
	int				cmd;
	int				sep;
	int				ret;
	struct s_list	*next;
}				t_list;

typedef void     (*t_function)(t_list **);

void 	set_input(char *str, char **input);
int 	parsing(char *str, t_list **cmd_lst);
int		ft_error(t_list *cmd_lst);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		save_cmd(char *str, t_list **cmd_lst, int cmd);
t_list	*ft_listnew(int cmd);
void	ft_listadd_back(t_list **alst, t_list *new);
void    execute(t_list **cmd);
void    ft_exit(t_list **cmd_lst);
void    ft_pwd(t_list **cmd_lst);
void    ft_cd(t_list **cmd_lst);
void    ft_env(t_list **cmd_lst);
void    ft_export(t_list **cmd_lst);
void    ft_unset(t_list **cmd_lst);
void    ft_echo(t_list **cmd_lst);
int		deal_dollar(char *str, char **input, int *j);
int		deal_simple_quote(char *str, char **input, int *j, int dollar);
int		deal_double_quote(char *str, char **input, int *j);

#endif
