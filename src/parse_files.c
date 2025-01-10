/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:08 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 07:49:52 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// It is guaranteed that argc >= 3.
void	parse_files_bonus(int argc, char *argv[], t_data *data)
{
	if (data->has_here_doc == true)
	{
		proc_here_doc(argv, data);
		if (argc == 3)
		{
			if (close(data->in_fd) == -1)
				proc_err(data, EXIT_FAILURE, ERR_CLOSE, NULL);
			if (unlink(data->here_doc_path) == -1)
				proc_err(data, EXIT_FAILURE, ERR_UNLINK, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		data->in_fd = open(argv[1], O_RDONLY);
		if (data->in_fd == -1)
			proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[1]);
	}
	data->status = STATUS_OPEN_INFILE;
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
	if (data->out_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[argc - 1]);
	data->status = STATUS_OPEN_OUTFILE;
}

void	parse_files(int argc, char *argv[], t_data *data)
{
	data->in_fd = open(argv[1], O_RDONLY);
	if (data->in_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[1]);
	data->status = STATUS_OPEN_INFILE;
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
	if (data->out_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[argc - 1]);
	data->status = STATUS_OPEN_OUTFILE;
}
