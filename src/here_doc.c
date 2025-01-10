/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 17:00:44 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

bool	here_doc_error(char *argv[], t_data *data, int gnl_return_code)
{
	if (gnl_return_code != GNL_SUCCESS_FIN)
		proc_gnl_err(data, gnl_return_code);
	else
		ft_dprintf(2, "\npipex: warning: here-document delimited "
			"by end-of-file (wanted `%s')\n", argv[2]);
	return (false);
}

bool	here_doc_success(char *argv[], t_data *data, char *new_line)
{
	if (cmp_limiter(argv[2], new_line) == 0)
	{
		free(new_line);
		return (false);
	}
	else
	{
		write(data->in_fd, new_line, strlen(new_line));
		free(new_line);
		return (true);
	}
}

void	proc_here_doc(char *argv[], t_data *data)
{
	char	*new_line;
	int		gnl_return_code;
	bool	loop_flag;

	set_here_doc_path(data);
	data->in_fd = open(data->here_doc_path, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (data->in_fd == -1)
		exit_pipex(data, EXIT_FAILURE, ERR_OPEN, data->here_doc_path);
	data->status = STATUS_OPEN_INFILE;
	loop_flag = true;
	while (loop_flag)
	{
		if (ft_dprintf(1, "> ") == -1)
			exit_pipex(data, EXIT_FAILURE, ERR_WRITE, NULL);
		new_line = get_next_line(STDIN_FILENO, &gnl_return_code);
		if (new_line == NULL)
			loop_flag = here_doc_error(argv, data, gnl_return_code);
		else
			loop_flag = here_doc_success(argv, data, new_line);
	}
}
