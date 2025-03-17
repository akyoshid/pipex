/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:22 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:02:59 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

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
