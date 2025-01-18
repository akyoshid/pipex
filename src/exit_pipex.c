/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:24 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/18 18:31:46 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	print_err(int err_code, char *param)
{
	if (err_code == NO_ERROR || err_code == ERR_NOT_PRINT)
		return ;
	else if (err_code == ERR_PARAM)
		ft_dprintf(2, param);
	else if (err_code == ERR_OPEN || err_code == ERR_ACCESS)
		ft_dprintf(2, "pipex: %s: %s\n", param, strerror(errno));
	else if (err_code == ERR_READ)
		ft_dprintf(2, "pipex: read: %s\n", strerror(errno));
	else if (err_code == ERR_WRITE)
		ft_dprintf(2, "pipex: write: %s\n", strerror(errno));
	else if (err_code == ERR_PIPE)
		ft_dprintf(2, "pipex: pipe: %s\n", strerror(errno));
	else if (err_code == ERR_FORK)
		ft_dprintf(2, "pipex: fork: %s\n", strerror(errno));
	else if (err_code == ERR_DUP2)
		ft_dprintf(2, "pipex: dup2: %s\n", strerror(errno));
	else if (err_code == ERR_EXECVE)
		ft_dprintf(2, "pipex: execve: %s\n", strerror(errno));
	else if (err_code == ERR_CMDNOTFOUND)
		ft_dprintf(2, "pipex: %s: command not found\n", param);
}

void	exit_pipex(t_data *data, int exit_status, int err_code, char *param)
{
	print_err(err_code, param);
	if (data->status >= STATUS_PARSE_AST)
		clear_ast(data->ast_root);
	if (data->status >= STATUS_OPEN_OUTFILE)
		close(data->out_fd);
	if (data->status >= STATUS_OPEN_INFILE)
	{
		close(data->in_fd);
		if (data->has_here_doc == true)
			unlink(data->here_doc_path);
	}
	if (data->status >= STATUS_PARSE_ENVS)
		clear_env_list(data);
	exit(exit_status);
}
