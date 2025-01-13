/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/12 18:48:49 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	here_doc_delete_tab(char *new_line)
{
	int		count;

	count = 0;
	while (new_line[count] == '\t')
		count++;
	if (count > 0)
		ft_strlcpy(new_line, new_line + count, ft_strlen(new_line) + 1);
}

bool	here_doc_error(t_data *data, int gnl_return_code, t_heredoc *hd_data)
{
	if (gnl_return_code != GNL_SUCCESS_FIN)
		proc_gnl_err(data, gnl_return_code);
	else
		ft_dprintf(2, "\npipex: warning: here-document delimited "
			"by end-of-file (wanted `%s')\n", hd_data->limiter);
	return (false);
}

bool	here_doc_success(t_data *data, char *new_line, t_heredoc *hd_data)
{
	if (hd_data->leading_hyphen == true)
		here_doc_delete_tab(new_line);
	if (cmp_limiter(hd_data->limiter, new_line) == 0)
	{
		free(new_line);
		return (false);
	}
	else
	{
		if (hd_data->leading_hyphen == true)
			here_doc_delete_tab(new_line);
		if (write(data->in_fd, new_line, ft_strlen(new_line)) == -1)
		{
			free(new_line);
			exit_pipex(data, EXIT_FAILURE, ERR_WRITE, NULL);
		}
		free(new_line);
		return (true);
	}
}

void	proc_here_doc(char *argv[], t_data *data)
{
	t_heredoc	hd_data;
	bool		loop_flag;
	char		*new_line;
	int			gnl_return_code;

	set_here_doc_path(data);
	data->in_fd = open(data->here_doc_path, O_CREAT | O_EXCL | O_WRONLY, 0666);
	if (data->in_fd == -1)
		exit_pipex(data, EXIT_FAILURE, ERR_OPEN, data->here_doc_path);
	data->status = STATUS_OPEN_INFILE;
	parse_limiter(data, argv[2], &hd_data);
	loop_flag = true;
	while (loop_flag)
	{
		if (ft_dprintf(1, "> ") == -1)
			exit_pipex(data, EXIT_FAILURE, ERR_WRITE, NULL);
		new_line = get_next_line(STDIN_FILENO, &gnl_return_code);
		if (new_line == NULL)
			loop_flag = here_doc_error(data, gnl_return_code, &hd_data);
		else
			loop_flag = here_doc_success(data, new_line, &hd_data);
	}
	close_and_open_here_doc_file(data);
	print_here_doc(data);
}
