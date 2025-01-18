/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:08 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 17:15:28 by akyoshid         ###   ########.fr       */
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
			exit_pipex(data, EXIT_SUCCESS, NO_ERROR, NULL);
	}
	parse_files(argc, argv, data);
}

void	parse_files(int argc, char *argv[], t_data *data)
{
	if (data->has_here_doc == false)
	{
		data->in_fd = open(argv[1], O_RDONLY);
		if (data->in_fd == -1)
			exit_pipex(data, EXIT_FAILURE, ERR_OPEN, argv[1]);
		data->status = STATUS_OPEN_INFILE;
	}
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (data->out_fd == -1)
		exit_pipex(data, EXIT_FAILURE, ERR_OPEN, argv[argc - 1]);
	data->status = STATUS_OPEN_OUTFILE;
}
