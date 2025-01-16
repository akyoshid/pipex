/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 04:48:46 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/16 19:37:46 by akyoshid         ###   ########.fr       */
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

# define STATUS_INITIAL 0
# define STATUS_MALLOC_ENVS 1
# define STATUS_OPEN_INFILE 2
# define STATUS_OPEN_OUTFILE 3
# define STATUS_PARSE_AST 4

# define NO_ERROR -1
# define ERR_NOT_PRINT 0
# define ERR_PARAM 1
# define ERR_OPEN 2
# define ERR_READ 3
# define ERR_WRITE 4
# define ERR_CLOSE 5
# define ERR_UNLINK 6
# define ERR_MALLOC 7

# define RAND_SUCCESS 0
# define RAND_ERR_OPEN -1
# define RAND_ERR_READ_FAIL -2
# define RAND_ERR_READ_LACK -3
# define RAND_ERR_CLOSE -4
# define RAND_ERR_INVALID_LEN -5

typedef struct s_data
{
	struct s_env	*env_list;
	int				in_fd;
	int				out_fd;
	bool			has_here_doc;
	char			here_doc_path[23];
	struct s_ast	*ast_root;
	int				status;
}					t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_heredoc
{
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
}					t_ast;

// check_argc.c
void	check_argc_bonus(int argc, char *argv[], t_data *data);
void	check_argc(int argc, t_data *data);
// envs_utils.c
void	clear_env_list(t_data *data);
void	print_env_list(t_data *data);
// exit_pipex.c
void	print_err(int err_code, char *param);
void	set_exit_fail_and_print_err(
			int *exit_status, int err_code, char *param);
void	exit_pipex(t_data *data, int exit_status, int err_code, char *param);
// here_doc_limiter.c
int		cmp_limiter(char *limiter, char *new_line);
void	parse_limiter_quotation(
			char *limiter, t_heredoc *hd_data, int i, int len);
void	parse_limiter(t_data *data, char *limiter, t_heredoc *hd_data);
// here_doc_set_path.c
int		ft_rand_bytes(char *dst, int len);
void	set_here_doc_path(t_data *data);
// here_doc_var.c
int		calc_var_key_len(char *str);
char	*search_var_value(t_data *data, char *str);
char	*replace_by_var_value(
			char *src, int *i, int var_key_len, char *var_value);
char	*here_doc_expand_var(t_data *data, char *src);
// here_doc_utils.c
void	here_doc_delete_tab(char *new_line);
void	proc_gnl_err(t_data *data, int return_code);
void	close_and_open_here_doc_file(t_data *data);
void	print_here_doc(t_data *data);
// here_doc.c
bool	here_doc_error(t_data *data, int gnl_return_code, t_heredoc *hd_data);
bool	here_doc_success(t_data *data, char *new_line, t_heredoc *hd_data);
void	proc_here_doc(char *argv[], t_data *data);
// init_data.c
void	init_data(t_data *data);
// parse_ast_utils.c
void	print_ast(t_ast *node);
void	free_command_argv(char **argv);
void	clear_ast(t_ast *node);
// parse_ast.c
t_ast	*create_node(t_node_type type);
t_ast	*parse_command(char *arg);
t_ast	*wrapped_parse_command(char *arg, t_data *data, t_ast *root);
t_ast	*create_pipe(t_data *data, t_ast *left, t_ast *right);
t_ast	*parse_ast(int argc, char *argv[], t_data *data);
// parse_envs.c
t_env	*malloc_env(void);
void	add_back_env(t_data *data, t_env *new);
void	parse_envs(char *envp[], t_data *data);
// parse_files.c
void	parse_files_bonus(int argc, char *argv[], t_data *data);
void	parse_files(int argc, char *argv[], t_data *data);

#endif
