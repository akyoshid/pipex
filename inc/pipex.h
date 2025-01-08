/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 04:48:46 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/08 18:58:15 by akyoshid         ###   ########.fr       */
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

# define STATUS_BEFORE_OPEN_INFILE 0
# define STATUS_AFTER_OPEN_INFILE 1
# define STATUS_AFTER_OPEN_OUTFILE 2

# define ERR_PARAM 0
# define ERR_OPEN 1
# define ERR_READ 2
# define ERR_MALLOC 3
# define ERR_UNLINK 4

typedef struct s_data
{
	int		in_fd;
	int		out_fd;
	bool	has_here_doc;
	char	here_doc_path[23];
	char	**cmd_path;
	char	***cmd_args;
	int		status;
}			t_data;

// check_argc.c
void	check_argc_bonus(int argc, char *argv[], t_data *data);
void	check_argc(int argc, t_data *data);
// exit_pipex.c
void	exit_pipex(t_data *data);
// init_data.c
void	init_data(t_data *data);
// parse_files.c
int		ft_rand_bytes(char *dst, int len);
void	set_here_doc_path(t_data *data);
void	proc_here_doc(char *argv[], t_data *data);
void	parse_files_bonus(int argc, char *argv[], t_data *data);
void	parse_files(int argc, char *argv[], t_data *data);
// proc_err.c
void	print_err(int err_code, char *param);
void	proc_err(t_data *data, int exit_status, int err_code, char *param);

#endif
