/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:24 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/08 20:08:15 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exit_pipex(t_data *data)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (close(data->out_fd) == -1)
	{
		print_err(ERR_CLOSE, NULL);
		exit_status = EXIT_FAILURE;
	}
	if (close(data->in_fd) == -1)
	{
		print_err(ERR_CLOSE, NULL);
		exit_status = EXIT_FAILURE;
	}
	if (data->has_here_doc == true && unlink(data->here_doc_path) == -1)
	{
		print_err(ERR_UNLINK, NULL);
		exit_status = EXIT_SUCCESS;
	}
	exit(exit_status);
}
