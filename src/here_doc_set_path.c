/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_set_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:14 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/18 17:11:09 by akyoshid         ###   ########.fr       */
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

void	set_here_doc_path(t_data *data)
{
	char	rand[11];
	int		rand_rv;
	int		i;

	ft_strlcpy(data->here_doc_path, "/tmp/sh-thd-", 23);
	rand_rv = ft_rand_bytes(rand, 10);
	if (rand_rv == RAND_ERR_OPEN)
		exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_OPEN, "/dev/urandom");
	else if (rand_rv == RAND_ERR_READ_FAIL)
		exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_READ, NULL);
	else if (rand_rv == RAND_ERR_READ_LACK)
		exit_pipex(data, PIPEX_GENERAL_ERROR, ERR_PARAM, "pipex: "
			"ft_rand_bytes: Failed to read the specified number of bytes");
	i = 0;
	while (i < 10)
	{
		rand[i] = rand[i] % 36;
		if (rand[i] <= 9)
			data->here_doc_path[i + 12] = rand[i] + '0';
		else
			data->here_doc_path[i + 12] = rand[i] - 10 + 'a';
		i++;
	}
	data->here_doc_path[22] = '\0';
}
