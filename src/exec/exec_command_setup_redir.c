/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_setup_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:31:53 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:34:59 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

static int	_set_up_here_doc(t_ast *node, t_data *data)
{
	int	fd;

	if (proc_here_doc(node, data) == -1)
	{
		unlink(node->here_doc_path);
		return (PIPEX_GENERAL_ERROR);
	}
	fd = open(node->here_doc_path, O_RDONLY);
	if (fd == -1)
	{
		print_err(ERR_OPEN, node->here_doc_path);
		unlink(node->here_doc_path);
		return (PIPEX_GENERAL_ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		print_err(ERR_DUP2, NULL);
		close (fd);
		unlink(node->here_doc_path);
		return (PIPEX_GENERAL_ERROR);
	}
	close (fd);
	unlink(node->here_doc_path);
	return (0);
}

static int	_setup_redir_in(t_ast *node)
{
	int	fd;

	fd = open(node->redir_in_path, O_RDONLY);
	if (fd == -1)
	{
		print_err(ERR_OPEN, node->redir_in_path);
		return (PIPEX_GENERAL_ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		print_err(ERR_DUP2, NULL);
		close(fd);
		return (PIPEX_GENERAL_ERROR);
	}
	close(fd);
	return (0);
}

static int	_setup_redir_out(t_ast *node)
{
	int	fd;

	fd = open(node->redir_out_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		print_err(ERR_OPEN, node->redir_out_path);
		return (PIPEX_GENERAL_ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		print_err(ERR_DUP2, NULL);
		close(fd);
		return (PIPEX_GENERAL_ERROR);
	}
	close(fd);
	return (0);
}

int	setup_redirect(t_ast *node, t_data *data)
{
	if (node->here_doc_flag == true)
	{
		if (_set_up_here_doc(node, data) != 0)
			return (PIPEX_GENERAL_ERROR);
	}
	else if (node->redir_in_flag == true)
	{
		if (_setup_redir_in(node) != 0)
			return (PIPEX_GENERAL_ERROR);
	}
	if (node->redir_out_flag == true)
	{
		if (_setup_redir_out(node) != 0)
			return (PIPEX_GENERAL_ERROR);
	}
	return (0);
}
