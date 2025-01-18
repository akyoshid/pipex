/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:04:59 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/18 13:56:19 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	exec_command_fork_err(char *executable_path)
{
	print_err(ERR_FORK, NULL);
	free(executable_path);
	return (1);
}

void	exec_command_execve_err(void)
{
	print_err(ERR_EXECVE, NULL);
	exit(126);
}

int	exec_command(t_ast *node, t_data *data)
{
	char	*executable_path;
	int		return_value;
	pid_t	pid;
	int		status;

	// setup_redirect();
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
