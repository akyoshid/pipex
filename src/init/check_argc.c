/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:49:34 by akyoshid          #+#    #+#             */
/*   Updated: 2025/04/10 07:39:59 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

static void	_not_exec_any_cmds(
	char *infile_path, char *outfile_path, t_data *data)
{
	int	fd;

	if (infile_path != NULL)
	{
		fd = open(infile_path, O_RDONLY);
		if (fd == -1)
			exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_OPEN, infile_path);
		close (fd);
	}
	if (outfile_path != NULL)
	{
		if (data->has_here_doc == true)
			fd = open(outfile_path, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_OPEN, outfile_path);
		close (fd);
	}
	exit(PIPEX_SUCCESS);
}

static void	_not_exec_any_cmds_here_doc(
	char *word, char *outfile_path, t_data *data)
{
	t_ast	*node;
	int		fd;

	node = create_node(NODE_COMMAND);
	node->here_doc_flag = true;
	node->here_doc_word = word;
	if (proc_here_doc(node, data) == -1)
	{
		unlink(node->here_doc_path);
		free(node);
		exit_pipex(data, PIPEX_GENERAL_ERROR, NO_ERROR, NULL);
	}
	fd = open(node->here_doc_path, O_RDONLY);
	if (fd == -1)
	{
		print_err(ERR_OPEN, node->here_doc_path);
		unlink(node->here_doc_path);
		free(node);
		exit_pipex(data, PIPEX_GENERAL_ERROR, NO_ERROR, NULL);
	}
	close (fd);
	unlink(node->here_doc_path);
	free(node);
	_not_exec_any_cmds(NULL, outfile_path, data);
}

void	check_argc_bonus(int argc, char *argv[], t_data *data)
{
	if (argc == 1)
		exit(PIPEX_SUCCESS);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc") + 1) == 0)
	{
		data->has_here_doc = true;
		if (argc == 2)
			exit_pipex(data, PIPEX_SYNTAX_ERROR, ERR_PARAM,
				"pipex: syntax error near unexpected token `newline'\n");
		else if (argc == 3)
			_not_exec_any_cmds_here_doc(argv[2], NULL, data);
		else if (argc == 4)
			_not_exec_any_cmds_here_doc(argv[2], argv[3], data);
	}
	else
	{
		if (argc == 2)
			_not_exec_any_cmds(argv[1], NULL, data);
		else if (argc == 3)
			_not_exec_any_cmds(argv[1], argv[2], data);
	}
	if ((data->has_here_doc == false && argc >= 3337)
		|| (data->has_here_doc == true && argc >= 3338))
		exit_pipex(data, PIPEX_SYNTAX_ERROR, ERR_PARAM,
			"pipex: syntax error near unexpected token `|'\n");
}

void	check_argc(int argc, t_data *data)
{
	if (argc != 5)
	{
		exit_pipex(data, PIPEX_SYNTAX_ERROR, ERR_PARAM,
			"pipex: Invalid number of arguments\n"
			"Usage: ./pipex infile cmd1 cmd2 outfile\n");
	}
}
