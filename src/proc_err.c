/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:50:13 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/08 18:03:27 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	print_err(int err_code, char *param)
{
	if (err_code == ERR_PARAM)
		ft_dprintf(2, param);
	else if (err_code == ERR_OPEN || err_code == ERR_READ)
		ft_dprintf(2, "pipex: %s: %s\n", param, strerror(errno));
	else if (err_code == ERR_MALLOC)
		ft_dprintf(2, "pipex: malloc: %s\n", strerror(errno));
	else if (err_code == ERR_UNLINK)
		ft_dprintf(2, "pipex: unlink: %s\n", strerror(errno));
}

void	proc_err(t_data *data, int exit_status, int err_code, char *param)
{
	print_err(err_code, param);
	if (data->status >= STATUS_AFTER_OPEN_INFILE)
	{
		close (data->in_fd);
		if (data->has_here_doc == true && unlink(data->here_doc_path) == -1)
			print_err(ERR_UNLINK, NULL);
	}
	if (data->status >= STATUS_AFTER_OPEN_OUTFILE)
		close (data->out_fd);
	exit(exit_status);
}
