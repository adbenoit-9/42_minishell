/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 00:45:42 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/17 13:45:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <signal.h>
# include "../libft/inc/libft.h"

extern int	g_status;
extern int	g_wait;
extern int	g_tmp;
extern int	g_quote;

typedef struct	s_shell
{
	pid_t		pid;
	int			bool;
	int			sig;
	char		*pwd;
}				t_shell;

typedef struct	s_cmd
{
	t_list			*tok;
	t_list			*input;
	t_list			*output;
	char			*pwd;
	int				sep;
	int				r_type;
	int				err;
	struct s_cmd	*next;
}				t_cmd;

extern t_cmd	*g_cmd;
extern t_shell	g_shell;

typedef void	(*t_function)(t_cmd *, int *, char ***);

/*
**	UTILS
*/

int				error_msg(char *g_cmd, char *arg, char *err, int error);
int				errno_msg(char *cmd, char *str, int ret);
void			ft_cmdclear(t_cmd **lst, void (del)(t_cmd**));
void			clear_one(t_cmd **cmd);
int				check_var_name(char *var);
char			*ft_getenv(char *name, int *n, char *envp[]);
int				ft_putenv(char *name, char *str, char **envp[]);
int				ft_setenv(char *name, char *value, int mode, char **envp[]);
char			*get_var_name(char *name, char *str);

/*
**	PARSING
*/

int				set_token(char **tokens, t_cmd **cmd, char *envp[]);
int				parsing(char *str, char **envp[]);
int				save_cmd(char *str, t_cmd **cmd, char *envp[]);
t_cmd			*ft_cmdnew(int sep);
void			ft_cmdadd_back(t_cmd **alst, t_cmd *new);
int				deal_dollar(char *str, t_list **lst, int *j, char *envp[]);
int				deal_simple_quote(char *str, char *token, int *j, int dollar);
int				deal_double_quote(char *str, t_list **lst, int *j, char **envp);
int				set_sep(char *str, int *i);
int				ft_issep(char c);
int				sep_error(int s1, int s2, char *str);
char			**split_token(char const *s, char c, int n);
int				is_in_quote(char const *s, int i, int *quote);
int				parse_token(char *token, t_list **new, t_cmd **cmd, char **env);
int				parse_syntax(char *str);
int				deal_status(char **tokens, int *k, int size);
int				set_file_name(t_cmd **cmd, char *str, char *envp[]);

/*
**	COMMANDS
*/

void			ft_pwd(t_cmd *cmd, int *fd, char **envp[]);
void			ft_cd(t_cmd *cmd, int *fd, char **envp[]);
void			ft_env(t_cmd *cmd, int *fd, char **envp[]);
void			ft_exit(t_cmd *cmd, int *fd, char **envp[]);
void			ft_export(t_cmd *cmd, int *fd, char **envp[]);
void			ft_unset(t_cmd *cmd, int *fd, char **envp[]);
void			ft_echo(t_cmd *cmd, int *fd, char **envp[]);
void			ft_not_builtin(t_cmd *cmd, int *fd, char **envp[]);

void			ft_sortenv(char **env);
int				ft_redirect(t_cmd *cmd, int *fd_in, int *fd_out);
void			ft_fork_handle(t_cmd *cmd, char **envp[]);
int				ft_launch_process(t_cmd **cmd, char **args);
char			*ft_correct_path(char *path);
int				run_cmd(t_cmd *cmd, int *fd, int pid, char **envp[]);
int				ft_incr_shlvl(char ***envp);

void			proc_sig_handler(int signo);
void			ft_mana_sig(t_cmd *cmd);
void			ft_sig_handler(int signo);
void			init_mshell(void);
void			modify_fd(t_cmd *cmd, int *fd);

#endif
