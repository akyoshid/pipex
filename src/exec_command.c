/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:04:59 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/18 19:32:33 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	setup_redirect(t_ast *node, t_data *data)
{
	if (node->redir_in == true)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
		{
			print_err(ERR_DUP2, NULL);
			return (PIPEX_GENERAL_ERROR);
		}
	}
	if (node->redir_out == true)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		{
			print_err(ERR_DUP2, NULL);
			return (PIPEX_GENERAL_ERROR);
		}
	}
	return (0);
}

int	exec_command_fork_err(char *executable_path)
{
	print_err(ERR_FORK, NULL);
	free(executable_path);
	return (PIPEX_GENERAL_ERROR);
}

void	exec_command_execve_err(void)
{
	print_err(ERR_EXECVE, NULL);
	exit(PIPEX_CANNOT_EXEC);
}

int	exec_command(t_ast *node, t_data *data)
{
	char	*executable_path;
	int		return_value;
	pid_t	pid;
	int		status;

	if (setup_redirect(node, data) != 0)
		return (PIPEX_GENERAL_ERROR);
	return_value = check_executable_path(node->argv[0], data, &executable_path);
	if (return_value != 0)
		return (return_value);
	pid = fork();
	if (pid == -1)
		return (exec_command_fork_err(executable_path));
	else if (pid == 0)
	{
		execve(executable_path, node->argv, data->envp);
		exec_command_execve_err();
	}
	waitpid(pid, &status, 0);
	free(executable_path);
	return (get_exit_status(status));
}
