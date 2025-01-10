/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:22 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 17:00:15 by akyoshid         ###   ########.fr       */
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
	if (close(fd) == -1)
		return (RAND_ERR_CLOSE);
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
		exit_pipex(data, EXIT_FAILURE, ERR_OPEN, "/dev/urandom");
	else if (rand_rv == RAND_ERR_READ_FAIL)
		exit_pipex(data, EXIT_FAILURE, ERR_READ, NULL);
	else if (rand_rv == RAND_ERR_READ_LACK)
		exit_pipex(data, EXIT_FAILURE, ERR_PARAM, "pipex: "
			"ft_rand_bytes: Failed to read the specified number of bytes");
	else if (rand_rv == RAND_ERR_CLOSE)
		exit_pipex(data, EXIT_FAILURE, ERR_CLOSE, NULL);
	i = -1;
	while (++i < 10)
	{
		rand[i] = rand[i] % 36;
		if (rand[i] <= 9)
			data->here_doc_path[i + 12] = rand[i] + '0';
		else
			data->here_doc_path[i + 12] = rand[i] - 10 + 'a';
	}
	data->here_doc_path[22] = '\0';
}

void	proc_gnl_err(t_data *data, int return_code)
{
	if (return_code == GNL_FAILURE_MALLOC)
		exit_pipex(data, EXIT_FAILURE, ERR_MALLOC, NULL);
	else if (return_code == GNL_FAILURE_READ)
		exit_pipex(data, EXIT_FAILURE, ERR_READ, NULL);
	else
	{
		if (return_code == GNL_FAILURE_BUFFER_SIZE)
			ft_dprintf(STDERR_FILENO,
				"pipex: get_next_line: Invalid BUFFER_SIZE\n");
		else if (return_code == GNL_FAILURE_FD)
			ft_dprintf(STDERR_FILENO,
				"pipex: get_next_line: Invalid fd\n");
		exit_pipex(data, EXIT_FAILURE, ERR_NOT_PRINT, NULL);
	}
}

int	cmp_limiter(char *limiter, char *new_line)
{
	int		new_line_len;
	bool	trim_flag;
	int		return_value;

	new_line_len = ft_strlen(new_line);
	trim_flag = false;
	if (new_line[new_line_len - 1] == '\n')
	{
		new_line[new_line_len - 1] = '\0';
		trim_flag = true;
	}
	return_value = ft_strcmp(limiter, new_line);
	if (trim_flag == true)
		new_line[new_line_len - 1] = '\n';
	return (return_value);
}
