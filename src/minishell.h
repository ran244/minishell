/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:57:29 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 16:57:05 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <sys/stat.h>

typedef struct s_tokens
{
	int							type;
	char						*token;
	struct s_tokens				*next;
	struct s_tokens				*prev;
	struct s_tokens				*tail;
}								t_tokens;

typedef struct s_loads
{
	char						**command;
	char						**redirect;
	int							type;
	struct s_loads				*head;
	int							fd_in;
	int							fd_out;
	char						*hd_buffer;
	struct s_loads				*next;
	struct s_loads				*prev;
}								t_loads;

typedef struct s_info
{
	char						**copy_env;
	int							num_of_pipes;
	int							len_envvar;
	int							flag;
	int							stdout_copy;
	int							stdin_copy;
}								t_info;

typedef struct s_envir
{
	char						*key;
	char						*val;
	// char *envline;
	int							index;
	struct s_envir				*next;
	struct s_envir				*prev;
	struct s_envir				*tail;
}								t_envir;

typedef struct s_shell
{
	int							exit_status;
	int							redir_flag;
	t_tokens					*tokens;
	t_loads						*loads;
	t_info						*info;
	t_envir						*envi;
	// pid_t *pid;
}								t_shell;
typedef struct s_exec_context
{
	t_loads						*cur;
	pid_t						*pid;
	int							fd[2];
	int							prev_fd;
	int							i;
}								t_exec_context;

extern volatile sig_atomic_t	g_sig;

t_envir					*does_exist(t_envir *envi, char *var, int len);
t_loads					*get_head(t_loads *node);
int						is_pathy(char *v);
int						env_var(t_info **info, char **env);
int						ft_strlenn(char *str);
void					free_tokens(t_tokens **list);
int						ft_perror(int flag, char *str);
void					ft_exit(t_shell *shell,
							int exit_stat, int flag, char *str);
void					ft_exit2(t_tokens **list,
							t_info **info, t_envir **envi, t_loads **load);
void					free_copy_env(t_info **info);
char					*ft_substr(char const *s,
							unsigned int start, size_t len);
void					free_info(t_info *info);
void					free_2d_array(char **arr);
void					free_loads(t_loads *loads);

void					sigint_parent(int sig);
void					sigint_child(int sig);
void					after_child(int sig);
void					sig_mode(int sig);
void					es_signal(t_shell *shell);

int						find_closure(char *line, int i, char q);
int						handle_qoute_in_word(t_tokens **list,
							char *line, int i, char q);
int						handle_word(t_tokens **list, char *line, int i);
int						syntax_error(t_tokens **list);
int						t_tokenise(t_tokens **list, t_info **info, char *line);
int						is_splitter(char c);
int						handle_redirection(t_tokens **list, char *line, int i);
int						skip_space(char *line, int i);
int						handle_pipe(t_tokens **list,
							t_info **info, char *line, int i);

int						parcing(t_shell *shell,
							t_envir **eniv, t_tokens **list, t_info **info);
void					joining(char **val, char *var);
void					add_char(char **val, char c, int *i);
char					*find_replace(t_envir *envi, char *var);
char					*expand_es(t_shell *shell, int *i);
char					*expand_ds_special(t_shell *shell,
							t_tokens *list, int *i);
char					*expand_ds(t_shell *shell,
							t_envir *envi, t_tokens *list, int *i);
char					*expand_dq(t_shell *shell,
							t_envir *envi, t_tokens *list, int *i);
void					replace_token(t_tokens *tmp, char *res);
char					*expand(t_shell *shell,
							t_envir *eniv, t_tokens *list, t_info *info);
void					hehe(t_shell *shell, t_tokens *list, int *i,
							char **value);
char					*expand_sq(t_tokens *list, int *i);

int						handle_fork(t_shell *shell, t_exec_context *ctx);
int						preprocess_heredoc(t_shell *shell,
							t_envir *envi, t_loads *load);
int						add_env(t_envir **env, char *line, int pi);
int						is_delimiter(char *line, char *tmp);
int						look_hd(char **redir);
int						prep_for_execute(t_tokens **list, t_loads **loads);
int						yalla_init(t_shell *shell,
							int *prev_fd, int *i, int **pid);
int						init_exec_context(t_shell *shell, t_exec_context *ctx);
int						add(t_tokens **list, char *command, int ty);
int						get_command_num(t_loads **load);
int						process_node(t_shell *shell, t_exec_context *ctx);
int						isqouted(char *del);
int						execute(t_shell *shell);
int						prepare_node(t_loads **loads, t_tokens **tmp);
int						is_redirect(char *arr);
int						handle_input_redir(char **redir, int i, t_shell *shell);
int						handle_output_redir(char **redir,
							int i, t_shell *shell, int append);
int						handle_heredoc_redir(char **redir,
							int i, t_loads *load, t_shell *shell);
int						handle_redi(char **redir, t_loads **load,
							t_shell *shell);
int						redirection_in(char *in, int outfd);
int						redirection_out(char *out, int infd, int flag);
int						write_to_pipe(int *fd, t_loads **load);
int						read_from_pipe(int *fd, t_loads **load);
int						prep_child(t_loads *cur, int prev_fd, int *fd);
int						handle_solo_builtin(t_shell *shell,
							t_exec_context *ctx, t_loads *cur);
int						is_solo_builtin(t_shell *shell, t_loads *cur);
int						is_path(char *v);
void					delete_node(t_envir **head, t_envir *node);
void					add_node(t_envir **envi, t_envir *tmp);
void					assign_type(t_tokens **tmp);
void					addback(t_tokens **list, t_tokens *tmp);
void					child_process(t_shell *shell,
							t_exec_context *ctx, t_loads *cur, pid_t *pid);
void					parent_cleanup(int *prev_fd,
							t_loads *cur, int *fd, pid_t pid);
void					clean_child(t_shell *shell, t_exec_context *ctx);
void					restore_std_fds(t_info *info);
void					finalize_exec(t_shell *shell,
							t_info *info, pid_t *pid, int count);
void					move(t_loads **cur);
char					*append_line(char *buf, char *line);
char					*expand_ds_var(t_envir *envi,
							char *line, int *i, int start);
char					*expand_ds_line(t_shell *shell,
							t_envir *envi, char *line, int *i);
char					*expand_line(t_shell *shell, t_envir *envi, char *line);
char					*expand_if_needed(char *line, int flag,
							t_shell *shell, t_envir *env);
char					*append_and_check(char *buf,
							char *line, char *tmp);
char					*hd_loop(t_shell *shell,
							t_envir *env, char *del, int flag);
char					*read_hd(t_shell *shell,
							t_envir *envi, char **redirect);
char					*init_tmp(char *del, int flag);
void					check_exec(t_loads *cur, t_shell *shell, int *fd);
void					free_them_all(t_shell *shell,
							char *str, pid_t **pid, int exit);
char					**ft_split_dir(char *str);
char					*get_path_value(t_envir *env);
char					*get_command_path_if_direct(char *cmd);
char					*search_in_path(char **paths, char *cmd);
char					*full_path(char *cmd, t_envir *env);
char					**alloc_and_copy(char **arr, int len);
char					**add_token(char **arr, char *token);
t_loads					*create_node(char **cmd, char **redir, int type);
void					append_node(t_loads **head, char **cmd, char **redir);
void					setup_pipe(int *fd);

int						pwd(t_envir **envi);
int						get_parent_len(char *dir);
int						get_builtin_flag(char *cmd);
int						is_builtin(char **v);
int						change_pd(t_envir **envi, char *target, char *cwd);
int						execut_built_in(t_shell *shell,
							t_exec_context *ctx, char **v, int flag);
int						cd(t_envir **envi, char **v);
int						find_n(char *command);
int						check_n(char *command);
int						parse_n_flags(char **cmd, int *start_idx);
int						set_env(t_envir **envi, char *key, char *res);
int						unset(t_envir **envi, char **v);
int						find_v_len(char **v);
int						is_valid_arg(char *v);
int						mini_exit(t_shell **shell,
							t_exec_context **ctx, char **v);
int						echo(char **cmd);
int						env(t_envir **envi);
int						is_valid(char *var);
int						export_args(t_envir *envi, t_info *info, char **v,
							int *flag);
int						export(t_envir **envi, t_info **info, char **argv);
int						findvarlen(char *var);
int						ft_strcmp(char *s1, char *s2);
int						ft_strchrr(const char *str, int s);
int						init_env(t_envir **envi, t_info **info, char **env);
int						export_noarg(t_envir *envi, t_info *info);
char					*get_parent_dir(char *dir);
char					*decide_target(t_envir **envi, char **v, char *cwd);
void					free_things(char **target, char **cwd);
char					*get_env_val(t_envir **envi, char *key);
void					sort_alpha(t_envir *envi);
void					replace_envlist(t_envir *tmp, char *res);
void					print_env(t_envir *head);
void					free_envvar(t_envir **env_var);
char					*fill_line(t_envir *envi);
void					freearr(char **arr);
char					**copy_env(t_envir *envi, t_info *info);
int						is_directory(const char *path);
#endif
