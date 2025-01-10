/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:24 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 18:05:41 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	print_err(int err_code, char *param)
{
	if (err_code == NO_ERROR || err_code == ERR_NOT_PRINT)
		return ;
	else if (err_code == ERR_PARAM)
		ft_dprintf(2, param);
	else if (err_code == ERR_OPEN)
		ft_dprintf(2, "pipex: %s: %s\n", param, strerror(errno));
	else if (err_code == ERR_READ)
		ft_dprintf(2, "pipex: read: %s\n", strerror(errno));
	else if (err_code == ERR_WRITE)
		ft_dprintf(2, "pipex: write: %s\n", strerror(errno));
	else if (err_code == ERR_CLOSE)
		ft_dprintf(2, "pipex: close: %s\n", strerror(errno));
	else if (err_code == ERR_UNLINK)
		ft_dprintf(2, "pipex: unlink: %s\n", strerror(errno));
	else if (err_code == ERR_MALLOC)
		ft_dprintf(2, "pipex: malloc: %s\n", strerror(errno));
}

void	set_exit_fail_and_print_err(int *exit_status, int err_code, char *param)
{
	*exit_status = EXIT_FAILURE;
	print_err(err_code, param);
}

void	exit_pipex(t_data *data, int exit_status, int err_code, char *param)
{
	print_err(err_code, param);
	if (data->status >= STATUS_OPEN_OUTFILE && close(data->out_fd) == -1)
		set_exit_fail_and_print_err(&exit_status, ERR_CLOSE, NULL);
	if (data->status >= STATUS_OPEN_INFILE)
	{
		if (close(data->in_fd) == -1)
			set_exit_fail_and_print_err(&exit_status, ERR_CLOSE, NULL);
		if (data->has_here_doc == true && unlink(data->here_doc_path) == -1)
			set_exit_fail_and_print_err(&exit_status, ERR_UNLINK, NULL);
	}
	if (data->status >= STATUS_MALLOC_ENVS)
		clear_env_list(data);
	exit(exit_status);
}
