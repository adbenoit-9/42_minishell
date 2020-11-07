/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:35:32 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 14:15:40 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define ECHO 0
# define CD 1
# define PWD 2
# define ENV 3
# define EXPORT 4
# define UNSET 5
# define EXIT 6
# define UNKNOW 7
# define ERROR 9
# define NUM_CMD 7

# define NONE -1
# define PIPE 0
# define COMA 1
# define RIGHT 2
# define LEFT 3
# define D_RIGHT 4
# define D_LEFT 5
# define AND 6
# define OR 7
# define NUM_SEP 5

# define EXIT_ERROR -6
# define FILE_ERR -5
# define MALL_ERR -4
# define SEP_ERR -3
# define QUOTE_NOT_FOUND -2
# define VAR_NOT_FOUND -1

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft_header/libft.h"

int g_status;

typedef struct	s_stock
{
	char			**tokens;
	char			*input;
	char			*output;
	int				sep;
	int				r_type;
	int				err;
	struct s_stock	*next;
}				t_stock;

extern t_stock	*g_cmd;

typedef void     (*t_function)(t_stock **, char **);

void	*ft_realloc(void *ptr, int newsize);
char	**realloc_tab(char **ptr, int newsize);
void	*ft_free(char **tab);
int		set_token(char **tokens, t_stock **cmd, char **envp);
int 	parsing(char *str, char *envp[]);
int		save_cmd(char *str, t_stock **cmd, char *envp[]);
t_stock	*ft_stocknew(int sep);
void	ft_stockadd_back(t_stock **alst, t_stock *new);
int	    execute(t_stock *cmd, char *envp[]);
void    ft_exit(t_stock **cmd, char *envp[]);
void    ft_pwd(t_stock **cmd, char *envp[]);
void    ft_cd(t_stock **cmd, char *envp[]);
void    ft_env(t_stock **cmd, char *envp[]);
void    ft_export(t_stock **cmd, char *envp[]);
void    ft_unset(t_stock **cmd, char *envp[]);
void    ft_echo(t_stock **cmd, char *envp[]);
void	ft_unknow(t_stock **cmd, char *envp[]);
int		deal_dollar(char *str, char **tokens, int *j, char *envp[]);
int		deal_simple_quote(char *str, char **tokens, int *j, int dollar);
int		deal_double_quote(char *str, char **tokens, int *j, char *env[]);
int		find_var(char *envp[], char *var);
int		print_error(char *g_cmd, char *arg, char *err, int error);
int		print_errno(char *cmd, char *str, int ret);
void	ft_stockclear(t_stock **lst, void (del)(t_stock**));
void	clear_one(t_stock **cmd);
int		replace_var_by_value(char *var, char *envp[], char **value, int *start);
int		set_sep(char *str, size_t *i);
int		ft_issep(char c, char before);
int		sep_error(int s1, int s2);
int		ft_redirect(t_stock **cmd, int *fd_in, int *fd_out);
char	**split_token(char const *s, char c, size_t n);
int		is_in_quote(char const *s, size_t *i, int quote);
int		is_bs(char *str, size_t *i);
int		parse_token(char *token, char **new_token, t_stock **cmd, char **envp);
int		parse_str(char *str);
int		deal_status(char **new_token, int *k, int size);
char	**ft_copy_tab(char *envp[]);
void	ft_sort_env(char *envp[]);
int		ft_arg_env(t_stock **cmd);
void    ft_loop_pipe(t_stock **cmd, char *envp[]);
int		ft_launch_process(t_stock **cmd, char **args, char *envp[]);
int		ft_try_path(t_stock **cmd, char *envp[], char *args[]);
size_t	ft_tabsize(char **tab);
int		set_file_name(t_stock **cmd, char *str, char **envp);

#endif
