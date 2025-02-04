/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 04:48:46 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/19 18:59:30 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line_bonus.h"

# define PIPEX_SUCCESS 0
# define PIPEX_GENERAL_ERROR 1
# define PIPEX_SYNTAX_ERROR 2
# define PIPEX_CANNOT_EXEC 126
# define PIPEX_CMD_NOT_FOUND 127

# define NO_ERROR 0
# define ERR_PARAM 1
# define ERR_OPEN 2
# define ERR_READ 3
# define ERR_WRITE 4
# define ERR_PIPE 5
# define ERR_FORK 6
# define ERR_DUP2 7
# define ERR_CMDNOTFOUND 8
# define ERR_ACCESS 9
# define ERR_EXECVE 10
# define ERR_WAITPID 11

# define RAND_SUCCESS 0
# define RAND_ERR_OPEN -1
# define RAND_ERR_READ_FAIL -2
# define RAND_ERR_READ_LACK -3
# define RAND_ERR_INVALID_LEN -4

typedef struct s_data
{
	char			**envp;
	struct s_env	*env_list;
	bool			has_here_doc;
	struct s_ast	*ast_root;
}					t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_heredoc
{
	int		fd;
	char	*limiter;
	bool	leading_hyphen;
	bool	quoted_limiter;
	bool	in_quotation;
	bool	single_quote;
}			t_heredoc;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**argv;
	bool			redir_in_flag;
	bool			redir_out_flag;
	bool			here_doc_flag;
	char			*redir_in_path;
	char			*redir_out_path;
	char			*here_doc_word;
	char			here_doc_path[23];
}					t_ast;

// check_argc.c
void	not_exec_any_cmds(char *infile_path, char *outfile_path, t_data *data);
void	not_exec_any_cmds_here_doc(
			char *word, char *outfile_path, t_data *data);
void	check_argc_bonus(int argc, char *argv[], t_data *data);
void	check_argc(int argc, t_data *data);
// envs_utils.c
char	*search_var_value(t_data *data, char *str);
void	clear_env_list(t_data *data);
void	print_env_list(t_data *data);
// exec_ast_utils.c
void	proc_err_waitpid(int *status);
int		get_exit_status(int status);
// exec_ast.c
int		exec_ast(t_ast *node, t_data *data);
// exec_command_setup_redir.c
int		set_up_here_doc(t_ast *node, t_data *data);
int		setup_redir_in(t_ast *node);
int		setup_redir_out(t_ast *node);
int		setup_redirect(t_ast *node, t_data *data);
// exec_command.c
int		exec_command_fork_err(char *executable_path);
void	exec_command_execve_err(void);
int		exec_command(t_ast *node, t_data *data);
// exec_pipe.c
int		exec_pipe_left_fork_err(int fd[]);
int		exec_pipe_right_fork_err(int fd[], pid_t pid_left, int *status_left_p);
void	exec_pipe_left(t_ast *node, t_data *data, int fd[]);
void	exec_pipe_right(t_ast *node, t_data *data, int fd[]);
int		exec_pipe(t_ast *node, t_data *data);
// executable_path_utils.c
char	*set_executable_path_dup_cmd(char *cmd);
char	*set_executable_path_current_dir(char *cmd);
char	**split_env_path(char *env_path);
char	*join_slash_cmd(char *cmd);
char	*set_executable_path_path_list_i(
			char **path_list, int i, char *slash_cmd);
// executable_path.c
char	*set_executable_path(char *cmd, t_data *data);
int		check_executable_path(
			char *cmd, t_data *data, char **executable_path_p);
// exit_pipex.c
void	exit_pipex(t_data *data, int exit_status, int err_code, char *param);
// here_doc_limiter.c
int		cmp_limiter(char *limiter, char *new_line);
void	parse_limiter_quotation(
			char *limiter, t_heredoc *hd_data, int i, int len);
int		parse_limiter(char *limiter, t_heredoc *hd_data);
// here_doc_set_path.c
int		ft_rand_bytes(char *dst, int len);
int		proc_err_ft_rand_bytes(int return_value);
int		set_here_doc_path(t_ast *node);
// here_doc_var.c
int		calc_var_key_len(char *str);
char	*replace_by_var_value(
			char *src, int *i, int var_key_len, char *var_value);
char	*here_doc_expand_var(t_data *data, char *src);
// here_doc_utils.c
void	here_doc_delete_tab(char *new_line);
int		proc_gnl_err(int return_code);
void	print_here_doc(t_ast *node);
// here_doc.c
int		here_doc_error(int gnl_return_code, t_heredoc *hd_data);
int		here_doc_success(t_data *data, char *new_line, t_heredoc *hd_data);
int		proc_here_doc(t_ast *node, t_data *data);
// init_data.c
void	init_data(t_data *data, char *envp[]);
// parse_ast_utils.c
void	print_ast(t_ast *node);
void	free_command_argv(char **argv);
void	clear_ast(t_ast *node);
// parse_ast.c
t_ast	*create_node(t_node_type type);
t_ast	*parse_command(int argc, char *argv[], t_data *data, int i);
t_ast	*create_pipe(t_ast *left, t_ast *right);
t_ast	*parse_ast(int argc, char *argv[], t_data *data);
// parse_envs.c
t_env	*malloc_env(void);
void	add_back_env(t_data *data, t_env *new);
void	parse_envs(char *envp[], t_data *data);
// print_err.c
void	print_err(int err_code, char *param);
// utils.c
void	free_2d_array(char **ptr);
// xmalloc.c
void	abort_memory_err(char *func_name);
void	*xmalloc(size_t bytes);

#endif
