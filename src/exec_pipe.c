/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:04:07 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/17 17:04:34 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	exec_pipe(t_ast *node, t_data *data)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	if (pipe(fd) == -1)
	{
		print_err(ERR_PIPE, NULL);
		return (1);
	}
	pid_left = fork();
	if (pid_left == -1)
	{
		print_err(ERR_FORK, NULL);
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	else if (pid_left == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			print_err(ERR_DUP2, NULL);
			close(fd[1]);
			exit(1);
		}
		close(fd[1]);
		exit(exec_ast(node->left, data));
	}
	pid_right = fork();
	if (pid_right == -1)
	{
		print_err(ERR_FORK, NULL);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid_left, &status_left, 0);
		return (1);
	}
	else if (pid_right == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			print_err(ERR_DUP2, NULL);
			close(fd[0]);
			exit(1);
		}
		close(fd[0]);
		exit(exec_ast(node->right, data));
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	return (get_exit_status(status_right));
}
