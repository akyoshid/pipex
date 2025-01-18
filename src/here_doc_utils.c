/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:22 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/18 18:37:33 by akyoshid         ###   ########.fr       */
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

void	proc_gnl_err(t_data *data, int return_code)
{
	if (return_code == GNL_FAILURE_MALLOC)
		abort_memory_err("get_next_line");
	else if (return_code == GNL_FAILURE_READ)
		exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_READ, NULL);
	else
	{
		if (return_code == GNL_FAILURE_BUFFER_SIZE)
			ft_dprintf(STDERR_FILENO,
				"pipex: get_next_line: Invalid BUFFER_SIZE\n");
		else if (return_code == GNL_FAILURE_FD)
			ft_dprintf(STDERR_FILENO,
				"pipex: get_next_line: Invalid fd\n");
		exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_NOT_PRINT, NULL);
	}
}

void	close_and_open_here_doc_file(t_data *data)
{
	close(data->in_fd);
	data->in_fd = open(data->here_doc_path, O_RDONLY);
	if (data->in_fd == -1)
	{
		print_err(ERR_OPEN, data->here_doc_path);
		unlink(data->here_doc_path);
		data->status--;
		exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_NOT_PRINT, NULL);
	}
}

void	print_here_doc(t_data *data)
{
	char	*new_line;
	int		gnl_return_code;

	while (1)
	{
		new_line = get_next_line(data->in_fd, &gnl_return_code);
		if (new_line == NULL && gnl_return_code == 0)
			return ;
		else if (new_line == NULL && gnl_return_code != 0)
		{
			ft_printf("gnl error\n");
			return ;
		}
		ft_printf("%s", new_line);
		free(new_line);
	}
	close_and_open_here_doc_file(data);
}
