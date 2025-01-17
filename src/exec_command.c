/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:04:59 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/17 17:05:45 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*find_command(char *cmd, t_data *data)
{
	(void)data;
	return(cmd);
}

int	exec_command(t_ast *node, t_data *data)
{
	char	*path;
	pid_t	pid;
	int		status;

	// setup_redirect();
	path = find_command(node->argv[0], data);
	if (path == NULL)
	{
		print_err(ERR_CMDNOTFOUND, node->argv[0]);
		return (127);
	}
	if (access(path, X_OK) == -1)
	{
		print_err(ERR_ACCESS, path);
		free(path);
		return (126);
	}
	pid = fork();
	if (pid == -1)
	{
		print_err(ERR_FORK, NULL);
		free(path);
		return (1);
	}
	else if (pid == 0)
	{
		execve(path, node->argv, data->envp);
		print_err(ERR_EXECVE, NULL);
		exit(126);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		return (get_exit_status(status));
	}
}
