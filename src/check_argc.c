/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:49:34 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/07 15:25:57 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	check_argc_bonus(int argc, char *argv[], t_data *data)
{
	if (argc == 1)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(argv[1], "here_doc", strlen("here_doc") + 1) == 0)
	{
		data->has_here_doc = true;
		if (argc == 2)
			proc_err(EXIT_FAILURE, ERR_PARAM,
				"pipex: syntax error near unexpected token `newline'\n");
	}
	else
	{
		if (argc == 2)
			proc_err(EXIT_FAILURE, ERR_PARAM,
				"pipex: Invalid number of arguments\n"
				"Usage: ./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile\n");
	}
}

void	check_argc(int argc)
{
	if (argc != 5)
	{
		proc_err(EXIT_FAILURE, ERR_PARAM,
			"pipex: Invalid number of arguments\n"
			"Usage: ./pipex infile cmd1 cmd2 outfile\n");
	}
}
