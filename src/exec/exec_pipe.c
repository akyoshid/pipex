/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:04:07 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:47:40 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

static int	_exec_pipe_left_fork_err(int fd[])
{
	print_err(ERR_FORK, NULL);
	close(fd[0]);
	close(fd[1]);
	return (PIPEX_GENERAL_ERROR);
}

static int	_exec_pipe_right_fork_err(
	int fd[], pid_t pid_left, int *status_left_p)
{
	print_err(ERR_FORK, NULL);
	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid_left, status_left_p, 0) == -1)
		proc_err_waitpid(status_left_p);
	return (PIPEX_GENERAL_ERROR);
}

static void	_exec_pipe_left(t_ast *node, t_data *data, int fd[])
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		print_err(ERR_DUP2, NULL);
		close(fd[1]);
		exit(PIPEX_GENERAL_ERROR);
	}
	close(fd[1]);
	exit(exec_ast(node->left, data));
}

static void	_exec_pipe_right(t_ast *node, t_data *data, int fd[])
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		print_err(ERR_DUP2, NULL);
		close(fd[0]);
		exit(PIPEX_GENERAL_ERROR);
	}
	close(fd[0]);
	exit(exec_ast(node->right, data));
}

int	exec_pipe(t_ast *node, t_data *data)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	if (pipe(fd) == -1)
		return (print_err(ERR_PIPE, NULL), PIPEX_GENERAL_ERROR);
	pid_left = fork();
	if (pid_left == -1)
		return (_exec_pipe_left_fork_err(fd));
	else if (pid_left == 0)
		_exec_pipe_left(node, data, fd);
	pid_right = fork();
	if (pid_right == -1)
		return (_exec_pipe_right_fork_err(fd, pid_left, &status_left));
	else if (pid_right == 0)
		_exec_pipe_right(node, data, fd);
	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid_left, &status_left, 0) == -1)
		proc_err_waitpid(&status_left);
	if (waitpid(pid_right, &status_right, 0) == -1)
		proc_err_waitpid(&status_right);
	return (get_exit_status(status_right));
}
