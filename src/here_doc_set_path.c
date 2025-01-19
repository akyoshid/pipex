/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_set_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:14 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/19 13:03:47 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_rand_bytes(char *dst, int len)
{
	int	fd;
	int	read_rv;

	if (len <= 0)
		return (RAND_ERR_INVALID_LEN);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (RAND_ERR_OPEN);
	read_rv = read(fd, dst, len);
	close(fd);
	if (read_rv == -1)
		return (RAND_ERR_READ_FAIL);
	else if (read_rv != len)
		return (RAND_ERR_READ_LACK);
	return (RAND_SUCCESS);
}

int	proc_err_ft_rand_bytes(int return_value)
{
	if (return_value == RAND_ERR_OPEN)
		print_err(ERR_OPEN, "/dev/urandom");
	else if (return_value == RAND_ERR_READ_FAIL)
		print_err(ERR_READ, NULL);
	else if (return_value == RAND_ERR_READ_LACK)
		print_err(ERR_PARAM, "pipex: ft_rand_bytes: "
			"Failed to read the specified number of bytes");
	return (-1);
}

int	set_here_doc_path(t_ast *node)
{
	char	rand[11];
	int		rand_rv;
	int		i;

	ft_strlcpy(node->here_doc_path, "/tmp/sh-thd-", 23);
	rand_rv = ft_rand_bytes(rand, 10);
	if (rand_rv != RAND_SUCCESS)
		return (proc_err_ft_rand_bytes(rand_rv));
	i = 0;
	while (i < 10)
	{
		rand[i] = rand[i] % 36;
		if (rand[i] <= 9)
			node->here_doc_path[i + 12] = rand[i] + '0';
		else
			node->here_doc_path[i + 12] = rand[i] - 10 + 'a';
		i++;
	}
	node->here_doc_path[22] = '\0';
	return (0);
}
