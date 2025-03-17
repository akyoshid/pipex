/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 04:48:46 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:42:52 by akyoshid         ###   ########.fr       */
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

enum e_error_code
{
	NO_ERROR,
	ERR_PARAM,
	ERR_OPEN,
	ERR_READ,
	ERR_WRITE,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP2,
	ERR_CMDNOTFOUND,
	ERR_ACCESS,
	ERR_EXECVE,
	ERR_WAITPID,
};

enum e_rand_return_value
{
	RAND_SUCCESS,
	RAND_ERR_OPEN,
	RAND_ERR_READ_FAIL,
	RAND_ERR_READ_LACK,
	RAND_ERR_INVALID_LEN,
};

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

// exec/
// exec/exec_ast_utils.c
void	proc_err_waitpid(int *status);
int		get_exit_status(int status);
// exec/exec_ast.c
int		exec_ast(t_ast *node, t_data *data);
// exec/exec_command_setup_redir.c
int		setup_redirect(t_ast *node, t_data *data);
// exec/exec_command.c
int		exec_command(t_ast *node, t_data *data);
// exec/exec_pipe.c
int		exec_pipe(t_ast *node, t_data *data);
// exec/executable_path_utils.c
char	*set_executable_path_dup_cmd(char *cmd);
char	*set_executable_path_current_dir(char *cmd);
char	**split_env_path(char *env_path);
char	*join_slash_cmd(char *cmd);
char	*set_executable_path_path_list_i(
			char **path_list, int i, char *slash_cmd);
// exec/executable_path.c
char	*set_executable_path(char *cmd, t_data *data);
int		check_executable_path(
			char *cmd, t_data *data, char **executable_path_p);

// here_doc/
// here_doc/cmp_limiter.c
int		cmp_limiter(char *limiter, char *new_line);
// here_doc/expand_var_here_doc.c
char	*expand_var_here_doc(t_data *data, char *src);
// here_doc/parse_limiter.c
int		parse_limiter(char *limiter, t_heredoc *hd_data);
// here_doc/set_here_doc_path.c
int		set_here_doc_path(t_ast *node);
// here_doc/proc_here_doc.c
int		proc_here_doc(t_ast *node, t_data *data);
// here_doc/utils.c
void	here_doc_delete_tab(char *new_line);
int		proc_gnl_err(int return_code);

// init/
// init/check_argc.c
void	check_argc_bonus(int argc, char *argv[], t_data *data);
void	check_argc(int argc, t_data *data);
// init/init_data.c
void	init_data(t_data *data, char *envp[]);
// init/parse_ast_utils.c
void	clear_ast(t_ast *node);
// init/parse_ast.c
t_ast	*create_node(t_node_type type);
t_ast	*parse_ast(int argc, char *argv[], t_data *data);
// init/parse_envs.c
void	parse_envs(char *envp[], t_data *data);

// utils/
// utils/envs_utils.c
char	*search_var_value(t_data *data, char *str);
void	clear_env_list(t_data *data);
void	print_env_list(t_data *data);
// utils/exit_pipex.c
void	exit_pipex(t_data *data, int exit_status, int err_code, char *param);
// utils/free_2d_array.c
void	free_2d_array(char **ptr);
// utils/print_err.c
void	print_err(int err_code, char *param);
// utils/xmalloc.c
void	abort_memory_err(char *func_name);
void	*xmalloc(size_t bytes);

#endif
