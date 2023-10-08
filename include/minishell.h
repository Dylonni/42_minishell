/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:18:02 by daumis            #+#    #+#             */
/*   Updated: 2023/09/27 17:31:06 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>

extern int	g_error;

typedef struct s_tkn
{
	char			*str;
	int				rtype;
	struct s_tkn	*next;
}	t_tkn;

typedef struct s_cmd
{
	t_tkn			**cmd_lst;
	char			**cmd;
	char			**final;
	t_tkn			**rdrct_lst;
	char			**rdrct;
	char			**rdrct_final;
	struct s_cmd	*next;
}	t_cmd;

/*Chained list element representing an element from envp
(Ex, Key -> GDMSESSION , Value -> ubuntu)*/
typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

/*This data structure is used only as a matter of gaining space.
Used by ft_quote_loop*/
typedef struct s_data
{
	int			index;
	int			index_prev;
	int			quote;
	int			dquote;
	int			size;
	char		*err;
	char		*cpy;
}	t_data;

/*Shell structure, useful data to execute commands 
and also storing the shell environement*/
typedef struct s_sh
{
	t_cmd			**cmds;
	t_var			**env_cpy;
	char			**env;
	t_var			**exp_cpy;
	pid_t			pid;
	int				status;
}	t_sh;

/*Pipe structure 
containing data related to pipes such as file descriptors or
the number of commands*/
typedef struct s_pipe
{
	int			fd[2];
	int			new_fd[2];
	int			old_fd[2];
	int			check;
	int			count;
	int			index;
	int			status;
}	t_pipe;

/*Exec structure , containing data such as pathnames needed for execve*/
typedef struct s_exec
{
	char	*pathname;
	char	**paths;
	int		command_found;
	int		i;
}	t_exec;

/*_____________Signals Handling_____________*/

void		ft_signal_c(int sig);
void		ft_signal_c_prnt(int sig);
void		ft_signal_c_exec(int sig);
void		ft_signal_c_hrdc(int sig);

void		ft_signal_backslash(int sig);
void		ft_signal_exec(void);
void		ft_signal_main(void);
void		ft_signal_hrdc(void);
int			event(void);

/*_____________Nodes Handling_____________*/

t_var		*ft_varnew(char *key, char *value);
void		ft_varadd_back(t_var **lst, t_var *new);
void		ft_varremove(t_var **lst, t_var *old);
void		ft_varprint_bis(t_var *tmp_var, int is_env);
void		ft_varprint(t_var **env_cpy, int is_env);

/*_____________Token Handling_____________*/

t_tkn		*ft_tknnew(char *str, int type);
void		ft_tknadd_back(t_tkn **lst, t_tkn *new);
void		ft_tknclear(t_tkn **lst);

int			ft_tknsize_quote(char *line, char c);
int			ft_tknsize_str(char *line);
int			ft_tknsize(char *line);
t_tkn		**ft_tkncreate(char *line);

/*_____________Command Handling_____________*/

t_cmd		*ft_cmdnew(void);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		ft_cmdclear(t_cmd **lst);
void		ft_cmdclear_tab(char **tab);
void		ft_cmdclear_loop(t_cmd **lst);

int			ft_cmdredirect_add(t_tkn ***rdrct, t_tkn **tkn, int type);
int			ft_cmdredirect(t_cmd **cmds, t_tkn **tkn);
int			ft_cmdloop(t_cmd **cmds, t_tkn **tkn);
t_cmd		**ft_cmdcreate(t_tkn **tokens);
int			ft_cmdcount(t_cmd **cmds);

/*_____________Expander Related Functions_____________*/

int			ft_xpnd_quote(char *str, t_data *data, int i);
int			ft_xpnd_dquote_bis(char *str, t_data *data, int i);
int			ft_xpnd_dquote(char *str, t_data *data, int i);
int			ft_xpnd_check(char *str, t_data *data);

int			ft_xpnd_size(t_tkn	*tmp_lst);
int			ft_xpnd_init(t_cmd *tmp_cmd);
int			ft_xpnd_rdrct_swap(t_cmd *tmp_cmd, t_var **env);

int			ft_xpnd_index(char *str);
char		*ft_findvalue(char *target, t_var **env);
t_var		*ft_findkey(char *target, t_var **env);
void		ft_xpnd_value_next(char **cmd, char *str,
				t_var **env, t_data *data);
void		ft_xpnd_value_first(char **cmd, char *str,
				t_var **env, t_data *data);

int			ft_quote_rdrct(t_cmd *tmp_cmd);
void		ft_quote_check(char *str, t_data *data, int *tab, int i);
int			ft_quote_fill(char *str, t_data *data, int *tab, char **final);
int			ft_quote_loop(char *str, char **final);
void		ft_quotehandler(t_cmd **cmds);

/*_____________Executor Related Functions_____________*/

int			ft_rdrct_checkin(t_cmd *cmd);
int			ft_rdrct_checkout(t_cmd *cmd);
int			ft_check_in(t_tkn *tmp_in, t_pipe *pipes);
int			ft_check_loop(t_tkn *tmp, t_pipe *pipes, t_sh *shell);
int			ft_check_files(t_cmd *cmd, t_pipe *pipes, t_sh *shell);

int			ft_strjoin_pathname(char **cmd, char **paths,
				int i, char **pathname);
void		ft_exec_error(void);
void		ft_close_pipes(t_pipe *pipes);
int			ft_execute_builtin(char **final, t_sh *shell);

int			ft_hrdc_wait(t_cmd *cmd);
int			ft_hrdc_ctrl(char *line);
int			ft_hrdc_loop(char *line, t_pipe *pipes, t_sh *shell);
int			ft_hrdc_read(char *lim, t_pipe *pipes, t_sh *shell, int *eof);
int			ft_heredoc(char *lim, t_pipe *pipes, t_sh *shell);

int			ft_execute_command(char **final, t_sh *shell);
int			ft_process_prnt(t_pipe *pipes);
int			ft_process_chld(t_cmd *cmd, t_sh *shell, t_pipe *pipes);
int			ft_execute_each(t_cmd *cmd, t_sh *shell, t_pipe *pipes);
int			ft_execute(t_cmd **cmds, t_sh *shell);

int			ft_absolute_path(char **final, t_exec *exec);
int			ft_relative_path(char **final, t_sh *shell, t_exec *exec);
int			ft_exec_cd(t_cmd **cmds, int count);
int			ft_exec_name(t_cmd **cmds, int count, char *name);
int			ft_execute_check(t_cmd **cmds, t_sh *shell, int count);

/*_____________Central Functions_____________*/

int			ft_xpnd_end(char **cmd, char *str, t_var **env, t_data *data);
int			ft_xpnd_loop(char **cmd, char *str, t_var **env);
int			ft_xpnd_fill(t_tkn **lst, char **cpy, t_var **env);
int			ft_expander(t_cmd **cmds, t_var **env);
int			ft_splitline(char *line, t_sh *shell);

int			ft_redirect_files(t_cmd *cmd, t_pipe *pipes, t_sh *shell);
void		ft_init_env_dfl(char **env, t_sh *shell);
int			ft_init_env(char **env, t_sh *shell);
void		ft_mainloop(t_sh *shell);

/*_____________Builtins Functions_____________*/

void		ft_cd(char **args, t_sh *shell);
void		ft_cd_bis(char *buf, t_var **env);

int			ft_echo_check(char *str);
void		ft_echo(char **args);

void		ft_env(char **args, t_sh *shell);
int			ft_env_child(t_sh *shell);
int			ft_env_child_bis(t_sh *shell, int size);

int			ft_atoll_check_bis(char *s, int *i, long long *res);
int			ft_atoll_check(char *s, int *i, long long *res, int sign);
long long	ft_atoll(char *s);
void		ft_exit(char **args);

int			ft_export_addexp(char **args, t_sh *shell, int i, char *value);
int			ft_export_addenv(char **args, t_sh *shell, int i, char *value);
int			ft_export_rmvenv(char **args, t_sh *shell, int i);
int			ft_export_check(char **args, t_sh *shell);
void		ft_export(char **args, t_sh *shell);

void		ft_pwd(char **args);

void		ft_export_apnd(char **args, t_sh *shell, int i);
int			ft_unset_rmvexp(char **args, t_sh *shell);
int			ft_unset_rmvenv(char **args, t_sh *shell);
int			ft_unset_check(char **args, t_sh *shell);
void		ft_unset(char **args, t_sh *shell);

/*_____________Utilities & Cleanup Functions_____________*/

int			ft_check_stat(char *path);

int			ft_whitespace(char c);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(const char *s, int len);
char		*ft_strjoin(char *s1, char *s2);

int			ft_isdigit(int c);
int			ft_isalnum(int c);
void		ft_putstr(char *str);
void		*ft_memset(void *s, int c, size_t n);
int			ft_checkspaces(char *str);

int			ft_strs_cnt(const char *str, char delimiter);
void		ft_str_len_tab(const char *str, char delimiter, int *strl_tab);
char		**ft_fill_strs(const char *str, char delimiter,
				int *nbr, int *str_len_tab);
void		ft_clearall(char **strs, int *nbr);
char		**ft_split(char const *s, char c);

int			slen(long nb);
char		*ft_itoa(int n);

void		ft_throw_err(char *err, int err_code);
void		ft_free_shell(t_sh *shell);
void		ft_free_env(char **env);
void		ft_free_exec(t_exec *exec);
void		ft_varclear(t_var **lst);

/*_____________ft_printf functions_____________*/

void		ft_hex(unsigned int nb, int *count, char c, int type);
void		ft_putptr(uintptr_t nb, int *count, int io, int type);

int			ismin(int nb, int *count, int type);
int			isnegmod(int nb, int *count, int type);
void		ft_putnbr(int nb, int *count, int type);

void		ft_putnbru(unsigned int nb, int *count, int type);

void		processtype(char c, va_list a_list, int *count, int type);
int			ft_printf(int type, const char *str, ...);

void		ft_putchar(char c, int *count, int type);

void		ft_putstrmod(const char *src, int *count, int type);

#endif