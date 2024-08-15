/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:46:56 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/15 18:56:40 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <errno.h>

/*COLORS*/
# define C_BLUE "\e[1;34m"
# define C_GREEN "\e[1;32m"
# define C_YELLOW "\e[1;93m"
# define C_MAGENTA "\e[1;35m"
# define C_CYAN "\e[1;96m"
# define C_RED "\e[6;31m"
# define END_COLOR "\e[0m"

/*DEFINE DOUBLE QUOTES AND SINGLE QUOTES*/
# define S_QUOTES 39
# define D_QUOTES 34

/*DEFINE ERROS*/
# define ERROR_PIPE_DOUBLE "syntax error near unexpected token `||'"
# define ERROR_PIPE_SINGLE "syntax error near unexpected token `|'"
# define ERROR_PIPE_FINAL "no support for this type of pipe"
# define ERROR_REDIR "syntax error near unexpected token `newline"
# define ERROR_REDIR_1 "syntax error near unexpected token `<'"
# define ERROR_QUOTE "quotation has not been closed"
# define ERROR_CD_MANY_ARGUMENT "cd: too many arguments"
# define ERR_HD "minishell: warning: here-document delimited by end-of-file\n"

typedef enum s_builtins
{
	not_builtin,
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	n_exit,
}			t_builtins;

typedef enum s_types
{
	string,
	flag,
	command,
	builtin,
	redin,
	redout,
	append,
	expander,
	is_pipe,
	here_doc,
	not_expander,
	MAIN,
	CHILD,
	HERE_DOC,
	PIPE,
	IGNORE,
}				t_types;

typedef enum e_tree_type
{
	t_exec,
	t_redir,
	t_pipe
}				t_tree_type;

typedef struct s_token
{
	char				*str;
	char				*exp;
	t_types				type;
	t_builtins			builtin;
	struct s_token		*next;
}				t_token;

/*TREE STRUCTS*/
typedef struct s_tree_root
{
	t_token		*token;
	t_tree_type	type;
}				t_tree_root;

typedef struct s_tree_pipe
{
	t_token		*token;
	t_tree_type	type;
	t_tree_root	*left;
	t_tree_root	*right;
}				t_tree_pipe;

typedef struct s_tree_red
{
	t_token		*token;
	t_tree_type	type;
	t_tree_root	*tree;
	char		*file;
	char		*exp;
	int			mode;
	int			fd;
	int			perm;
}				t_tree_red;

typedef struct s_tree_exec
{
	t_token		*token;
	t_tree_type	type;
	t_token		*builtin_token;
	char		*cmd;
	char		**argv;
}				t_tree_exec;

/*GENERAL STRUCTS*/
typedef struct s_envp
{
	char			*key;
	char			*value;
	int				invisible;
	struct s_envp	*next;
}					t_envp;

typedef struct s_data
{
	t_envp			*envp;
	t_token			*token;
	char			*home;
	char			*ex_;
	char			*shlvl;
	int				fd;
	int				fds[2];
	int				flag;
	int				hd;
	int				exit_code;
	int				pid;
	int				quotes;
	bool			split;
	t_tree_root		*tree;
	struct s_data	*next;
}				t_data;

extern int		g_exit_code;

/* ************************************************************************** */
/* ---------------------------------MAIN------------------------------------- */
/* ************************************************************************** */

/*MAIN*/
void		init_commands(char *buffer, t_data *data);
void		loop_minishell(t_data *data);
void		exec_minishell(t_data *data);
t_data		*init_minishell(int argc, char **argv, char **envp, t_data *data);

/*MAIN UTILS*/
void		have_pipe(t_data *data);
void		update_token(t_data *data);
bool		is_red_bool(t_token *token);
void		set_ex_(t_data *data);
void		search_command(char *buffer, t_data *data);

/*UTILS*/
void		*safe_calloc(size_t bytes, size_t n, t_data *data);
void		init_token(t_token *token, char *buffer);
void		init_next_token(t_token *token, int len);
void		init_data(t_data *data, char *buffer);
int			ft_strcmp(char *s1, char *s2);

/*SIGNALS*/
void		signal_here_doc(int signal_num);
void		signal_child(int signal_num);
void		signal_main(int signal_num);
void		ft_signal_def(void);

/*SIGNALS UTILS*/
void		ft_catch_signal(int fd);
void		reset_fd_signals(int fd1, int fd2);
void		ft_signal_ignore(void);
void		signal_heredoc(int signal, t_data *data, char *delimiter, \
char *here);

/*SIGNALS UTILS 2*/
void		sig_quit(int sig);
void		sig_int(int sig);
void		test_sigint(int signal);

/*EXIT_CODE*/
void		update_exit_code(int status, t_data *data);
void		set_exit_code(int code, t_data *data);
void		change_shlvl(t_data *data, char **envp);
void		catch_pid(t_data *data);

/* ************************************************************************** */
/* -------------------------------PARSING------------------------------------ */
/* ************************************************************************** */

/*CHECK FIRST*/
bool		valid_input(char *buffer, t_data *data);
bool		check_for_syntax_error(char *buffer, t_data *data);
bool		check_for_double_pipes(char *buffer);
bool		check_for_quotes(char *buffer, t_data *data);
bool		syntax_error_sup(char *buffer, t_data *data);

bool		check_valid_redir(char *buffer, int i);
bool		redirect_space_and_count_error(char *buffer);
bool		redirect_error(char *buffer);
bool		redirect_inverse_error(char *buffer);

void		redirect_error_suport(char *buffer, int i);
void		redirect_inverse_error_suport(char *buffer, int i);
bool		is_all_space(char *buffer);
bool		first_character(char *buffer);

/*DEAL WITH BUFFER*/
char		*check_spaces(char *buffer);
char		*put_space_on(char *buffer, int i);
char		*copy_char(char *buffer, int i);
char		*ft_strjoin_free(char *s1, char *s2);

int			move_space(char *buffer, int i);
bool		check_for_open_quotes(char *buffer, int i);
int			move_without_quotes(char *buffer, int i, t_data *data);
int			check_for_string(char *buffer, int start);

void		save_substring(char *buffer, int start, int end, t_data *data);
void		save_space(char *buffer, int start, t_data *data);
void		new_data(t_data *data, t_token *token);
void		pipe_split(t_data *data);
void		get_split(char *buffer, t_data *data);
int			find_token_end(char *buffer, int i);

/*DEFINE TOKENS*/
void		which_command(t_token *token);
void		define_tokens(t_token *token);
void		tokenize(t_data *data);
void		check_tokenize(t_data *data);

void		set_builtins(t_token *token, t_builtins	blt);
void		after_pipe(t_data *data);
void		is_red(t_token *token);
bool		is_red_or_pipe(t_token *token);

void		after_reds(t_data *data);
t_token		*trim_redir(t_data *data, t_token *token);
t_token		*trim_first_redir(t_data *data, t_token *token);
void		free_token_redir(t_token *token);

/*HERE_DOC*/
void		is_here_doc(t_data *data);
char		*remove_quotes_hd(char *delimiter);
char		*erase_the_quote_hd(char *delimiter, int i);
void		open_hd(t_data *data, t_token *token, char *delimiter, bool flag);
void		change_token(t_token *token, char *file);

void		fill_file(t_data *data, char *delimiter, char *file, bool flag);
void		write_file(char *here_doc_file, char *buffer);
char		*creat_here_doc_file(int i, bool flag);
bool		open_file(char *file);
char		*expansion_exit_code_hd(char *buffer, int j, int i, \
char *exit_code);

char		*expansion_hd(t_envp *envp, char *buffer, int j, int i);
char		*check_env_hd(char *buffer, t_envp *env, int j, int i);
char		*expansion_digit_hd(char *buffer, int j, int i);
char		*is_expand_util_hd(char *buffer, t_data *data, int i, int j);
char		*expand_hd(t_data *data, char *buffer, bool flag);

/*EXPAND*/
void		expansion_(t_data *data, t_token *token, int j);
void		expansion_dollar_sign(t_token *token, int j, int i, int pid);
void		expansion_digit(t_token *token, int j, int i);
void		expansion_exit_code(t_token *token, int j, int i, char *exit_code);
int			deal_with_quotes(t_token *token, int i);

bool		expansion(t_envp *envp, t_token *token, int j, int i);
void		check_env(t_token *token, t_data *data, int j, int i);
void		is_expand_util(t_token *token, t_data *data, int i, int j);
bool		is_expand_util_2(t_token *token, t_data *data, int i, int j);
void		expansion_special(t_token *token, int j);

void		expand_til(t_token *token, int i, char *home);
void		erase_dollar_sign(t_token *token, int i);
bool		is_expand_2(t_token *token, t_data *data, int i);
bool		is_expand(t_token *token, t_data *data);
void		expand(t_data *data);

void		update_tokenize(t_token *token_aux);
void		split_token(t_token *token);
t_token		*erase_token(t_data *data, t_token *token);
bool		all_space_or_null(t_token *token);
int			have_dquotes(t_token *token);

bool		have_spaces(char *str);

/*GET ENV*/
void		get_env(t_data *data, char **env);
void		cpy_(t_envp **env);
void		cpy_env(t_envp **env, char *str);
void		ft_lstadd_back_env(t_envp **lst, t_envp *new);
t_envp		*ft_lstnew_env(void *key, void *value);
void		empty_env(t_data *data);
t_envp		*have_variable(t_envp *env, char *key);

/*QUOTES*/
void		remove_quotes(t_data *data);
void		unquote_token(t_token *token);
int			deal_quotes(char *token, int i);
void		erase_the_quote(t_token *token, int i);

/*UTILS*/
int			ft_is_especial(int c);
int			ft_is_especial_2(int c);
char		*ft_strjoin_ex(char *s1, char const *s2);
int			quote_status(char *str, int i);

/* ************************************************************************** */
/* -------------------------------BUILTIN------------------------------------ */
/* ************************************************************************** */

/*GET_BUILTINS*/
void		get_builtin(t_data *data, t_token *token, int flag);
void		command_not_found(char *str, t_data *data);
void		ft_exit_flag(int exit_code, int exit_flag, t_data *data);

/*GET_ECHO*/
void		get_echo(t_token *token, t_data *data, int flag);
bool		need_space(t_token *token);

/*GET_ECHO_UTILS*/
void		echo_handle_tidle(t_data *data, t_token *token);

/*GET_PWD*/
void		get_pwd(t_token *token, t_data *data, int exit_flag);

/*GET_CD*/
void		get_cd(t_data *data, t_token *token, int exit_flag);

/*GET_CD_UTILS*/
void		cd_error_invalid_option(t_data *data, int exit_flag);
void		cd_error_invalid_file(t_data *data, t_token *token, int exit_flag);
char		*get_in_env(t_envp *envp, char *key);
t_envp		*change_in_env(t_envp *envp, char *cwd, char *key);
void		cd_error_no_file(t_data *data, int exit_flag);
bool		cd_change_last_oldpwd(t_data *data, int option);

/*GET_CD_UTILS_2*/
void		handle_plus_option(t_data *data, char *cwd, int exit_flag);
void		handle_minus_option(t_data *data, char *cwd, int exit_flag);
void		handle_tilde(t_data *data, t_token *token, int exit_flag,
				char *cwd);
bool		change_dir_update_env(t_data *data, char *old_cwd,
				char *old_cwd_char, int option);

/*GET_ENV*/
void		get_builtin_env(t_data *data, t_token *token, int exit_flag);
void		display_env(t_envp *envp, t_data *data, int exit_flag);

/*GET_EXIT*/
void		get_exit(t_data *data, t_token *token, int exit_flag);

/*GET_UTILS*/
void		exit_number(t_data *data, t_token *token, int exit_flag, \
int number);
void		free_to_exit(t_data *data);
long long	ft_atoll(const char *str);

/*GET_EXPORT*/
void		get_export(t_data *data, t_token *token, int exit_flag);
t_envp		*duplicate_envp_list(t_envp *env);
t_envp		*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env);
t_envp		*organize_envp_list(t_envp *duplicate_env);

/*GET_EXPORT_UTILS*/
void		display_env_export(t_envp *envp);
void		print_export(t_envp *env, t_data *data, int exit_flag);
t_envp		*find_last_node(t_envp *lst);
void		export_error_identifier(t_token *token, t_data *data, \
int exit_flag);

/*GET_EXPORT_UTILS_2*/
char		*find_key(char *str);
bool		is_invalid_token(char *key);
t_envp		*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env);
t_envp		*organize_envp_list(t_envp *duplicate_env);

/*GET_EXPORT_UTILS_3*/
bool		check_invalid_token(t_token *token);
void		print_error_option_export(t_token *token);

/*GET_UNSET*/
void		get_unset(t_data *data, t_token *token, int exit_flag);

/* ************************************************************************** */
/* -------------------------------ERROR-------------------------------------- */
/* ************************************************************************** */

void		free_token(t_token *token);
void		free_env(t_envp *envp);
void		free_data(t_data *data);
void		ft_free_data(t_data *data, int option);
void		*ptr_free(char **ptr);

void		clean(t_data *data, int ex);
void		clean_hd(t_data *data, int ex);
void		finished_exec(t_data *data, int exit_code);
void		unlink_here_doc_file(t_data *data);
void		free_tree(t_tree_root *cmd);

void		print_error(char *error_type, int error_code, t_data *data);
void		p_error_flag(char *error_type, int error_code, t_data *data, \
int exit_flag);

/* ************************************************************************** */
/* -----------------------------EXECUTION------------------------------------ */
/* ************************************************************************** */

int			count_args(t_data *data, t_token *token);
t_tree_root	*const_exec(t_data *data, t_token *token);
t_tree_root	*get_red(t_tree_root *red_cmd);
t_tree_root	*const_redir(t_tree_root *scmd, char *file, int mode, int fd);
t_tree_root	*const_pipe(t_data *data, t_tree_root *left, t_tree_root *right);

t_tree_root	*redir_struct(t_data *data, t_tree_root *tree_cmd);
void		get_exec(t_data *data, t_tree_exec *cmd, char *arg);
t_tree_root	*exec_struct(t_data *data, t_token *token);
t_tree_root	*pipe_struct(t_data *data, t_token *token);

void		exec_execution(t_data *data, t_tree_root *tree);
void		redir_execution(t_data *data, t_tree_root *tree);
void		clean_withou_exit(t_data *data);
void		executing_tree(t_data *data, t_tree_root *tree);
void		execution(t_data *data);

int			safe_fork(t_data *data);
char		**change_env(t_envp *envp);
void		safe_execve(t_data *data, t_tree_exec *exec);
void		safe_pipe(int fd[2], t_data *data);
void		pipe_child_execution(t_data *data, t_tree_root *tree, \
int fd[2], int proc);

char		*check_command(t_data *data, char *cmd, char *path);
char		*find_path(t_data *data, char *path, char *cmd);
char		*get_path(t_data *data, char *cmd);
void		empty_cmd(t_data *data, t_tree_exec *exec);
void		execve_error(t_data *data, char *exec_argv);

void		exec_no_pipes(t_data *data, t_tree_exec *tree);
void		cmd_execution(t_data *data, t_tree_exec *tree);
void		test_sigint2(int signal);
void		right_exit(int status);
void		pipe_execution(t_data *data, t_tree_root *tree);

/* ************************************************************************** */
/* -------------------------------DEBUG-------------------------------------- */
/* ************************************************************************** */

void		debug_print_list(t_data *data);
t_data		*debug_get_builtin_type(t_data *data);
void		free_cmd_type(t_tree_root *cmd);

#endif