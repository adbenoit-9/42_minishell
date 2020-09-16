/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:35:32 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/16 15:46:30 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define ECHO 0
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
#include <sys/errno.h>
#include "../libft/libft_header/libft.h"

typedef struct	s_stock
{
	char			*input;
	char			*output;
	int				cmd;
	int				sep;
	int				ret;
	int				err;
	struct s_stock	*next;
}				t_stock;

typedef void     (*t_function)(t_stock **, char **);

void	*ft_realloc(void *ptr, int newsize);
char	**realloc_tab(char **ptr, int newsize);
void 	set_input(char *str, t_stock **cmd_lst, char *envp[]);
int 	parsing(char *str, t_stock **cmd_lst, char *envp[]);
int		ft_error(t_stock **cmd_lst);
int		save_cmd(char *str, t_stock **cmd_lst, int cmd, char *envp[]);
t_stock	*ft_stocknew(int cmd);
void	ft_stockadd_back(t_stock **alst, t_stock *new);
void    execute(t_stock **cmd, char *envp[]);
void    ft_exit(t_stock **cmd_lst, char *envp[]);
void    ft_pwd(t_stock **cmd_lst, char *envp[]);
void    ft_cd(t_stock **cmd_lst, char *envp[]);
void    ft_env(t_stock **cmd_lst, char *envp[]);
void    ft_export(t_stock **cmd_lst, char *envp[]);
void    ft_unset(t_stock **cmd_lst, char *envp[]);
void    ft_echo(t_stock **cmd_lst, char *envp[]);
int		deal_dollar(char *str, t_stock **cmd_lst, int *j, char *envp[]);
int		deal_simple_quote(char *str, t_stock **cmd_lst, int *j, int dollar);
int		deal_double_quote(char *str, t_stock **cmd_lst, int *j, char *envp[]);
int		find_var(char *envp[], char *var);
char    *output_error(char *cmd, char *arg, char *err);
void	ft_stockclear(t_stock **lst, void (del)(t_stock**));
void	clear_one(t_stock **cmd_lst);
char	*replace_var_by_value(char *var, char *envp[], char *value, int *start);

#endif
