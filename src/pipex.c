/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:17:57 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/17 16:54:38 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	exec_ast(t_ast *node, t_data *data);

char	*find_command(char *cmd, t_data *data)
{
	(void)data;
	return(cmd);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (42);
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

int	exec_ast(t_ast *node, t_data *data)
{
	int	exit_status;

	if (node == NULL)
		return (0);
	if (node->type == NODE_COMMAND)
		exit_status = exec_command(node, data);
	else if (node->type == NODE_PIPE)
		exit_status = exec_pipe(node, data);
	return (exit_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		exit_status;

	init_data(&data, envp);
	check_argc(argc, &data);
	parse_envs(envp, &data);
	parse_files(argc, argv, &data);
	data.ast_root = parse_ast(argc, argv, &data);
	//
	print_ast(data.ast_root);
	ft_printf("\n");
	//
	exit_status = exec_ast(data.ast_root, &data);
	exit_pipex(&data, exit_status, NO_ERROR, NULL);
}
