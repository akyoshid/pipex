/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:49:08 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 11:42:32 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	abort_memory_err(char *func_name)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: out of virtual memory\n", func_name);
	exit(PIPEX_GENERAL_ERROR);
}

void	*xmalloc(size_t bytes)
{
	char	*temp;

	temp = malloc(bytes);
	if (temp == NULL)
		abort_memory_err("xmalloc");
	return (temp);
}
