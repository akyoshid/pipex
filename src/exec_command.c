/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:04:59 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/17 18:47:30 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*find_command(char *cmd, t_data *data)
{
	char	*path;

	(void)data;
	path = ft_strdup(cmd);
	return(path);
}

int	set_path(char *cmd, t_data *data, char **path_p)
{
	*path_p = find_command(cmd, data);
	if (*path_p == NULL)
	{
		print_err(ERR_CMDNOTFOUND, cmd);
		return (127);
	}
	if (access(*path_p, X_OK) == -1)
	{
		print_err(ERR_ACCESS, *path_p);
		free(*path_p);
		return (126);
	}
	return (0);
}

int	exec_command_fork_err(char *path)
{
	print_err(ERR_FORK, NULL);
	free(path);
	return (1);
}

void	exec_command_execve_err(void)
{
	print_err(ERR_EXECVE, NULL);
	exit(126);
}

int	exec_command(t_ast *node, t_data *data)
{
	char	*path;
	int		set_path_rv;
	pid_t	pid;
	int		status;

	// setup_redirect();
	set_path_rv = set_path(node->argv[0], data, &path);
	if (set_path_rv != 0)
		return (set_path_rv);
	pid = fork();
	if (pid == -1)
		return (exec_command_fork_err(path));
	else if (pid == 0)
	{
		execve(path, node->argv, data->envp);
		exec_command_execve_err();
	}
	waitpid(pid, &status, 0);
	free(path);
	return (get_exit_status(status));
}
