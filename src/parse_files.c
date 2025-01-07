/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:08 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/07 15:52:36 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// It is guaranteed that argc >= 3.
void	parse_files_bonus(t_data *data, int argc, char *argv[])
{
	if (data->has_here_doc == true)
	{
		// proc_here_doc();
		if (argc == 3)
		{
			// remove_here_doc_file();
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		data->in_fd = open(argv[1], O_RDONLY);
		if (data->in_fd == -1)
			proc_err(EXIT_FAILURE, ERR_OPEN, argv[1]);
	}
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
	if (data->out_fd == -1)
	{
		close(data->in_fd);
		proc_err(EXIT_FAILURE, ERR_OPEN, argv[1]);
	}
}

void	parse_files(t_data *data, int argc, char *argv[])
{
	data->in_fd = open(argv[1], O_RDONLY);
	if (data->in_fd == -1)
		proc_err(EXIT_FAILURE, ERR_OPEN, argv[1]);
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
	if (data->out_fd == -1)
	{
		close(data->in_fd);
		proc_err(EXIT_FAILURE, ERR_OPEN, argv[1]);
	}
}
