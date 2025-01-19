/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:22 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/19 17:37:13 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	here_doc_delete_tab(char *new_line)
{
	int		count;

	count = 0;
	while (new_line[count] == '\t')
		count++;
	if (count > 0)
		ft_strlcpy(new_line, new_line + count, ft_strlen(new_line) + 1);
}

int	proc_gnl_err(int return_code)
{
	if (return_code == GNL_FAILURE_MALLOC)
		abort_memory_err("get_next_line");
	else
	{
		if (return_code == GNL_FAILURE_READ)
			print_err(ERR_READ, NULL);
		else if (return_code == GNL_FAILURE_BUFFER_SIZE)
			print_err(ERR_PARAM,
				"pipex: get_next_line: Invalid BUFFER_SIZE\n");
		else if (return_code == GNL_FAILURE_FD)
			print_err(ERR_PARAM,
				"pipex: get_next_line: Invalid fd\n");
	}
	return (-1);
}

void	print_here_doc(t_ast *node)
{
	int		fd;
	char	*new_line;
	int		gnl_return_code;

	fd = open(node->here_doc_path, O_RDONLY);
	while (1)
	{
		new_line = get_next_line(fd, &gnl_return_code);
		if (new_line == NULL && gnl_return_code == 0)
			return ;
		else if (new_line == NULL && gnl_return_code != 0)
		{
			ft_printf("gnl error\n");
			return ;
		}
		ft_printf("%s", new_line);
		free(new_line);
	}
	close (fd);
}
