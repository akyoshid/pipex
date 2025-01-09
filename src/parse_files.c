/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:08 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/09 09:47:50 by akyoshid         ###   ########.fr       */
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
		proc_err(data, EXIT_FAILURE, ERR_OPEN, "/dev/urandom");
	else if (rand_rv == RAND_ERR_READ_FAIL)
		proc_err(data, EXIT_FAILURE, ERR_READ, NULL);
	else if (rand_rv == RAND_ERR_READ_LACK)
		proc_err(data, EXIT_FAILURE, ERR_PARAM, "pipex: "
			"ft_rand_bytes: Failed to read the specified number of bytes");
	else if (rand_rv == RAND_ERR_CLOSE)
		proc_err(data, EXIT_FAILURE, ERR_CLOSE, NULL);
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
		proc_err(data, EXIT_FAILURE, ERR_MALLOC, NULL);
	else if (return_code == GNL_FAILURE_READ)
		proc_err(data, EXIT_FAILURE, ERR_READ, NULL);
	else
	{
		if (return_code == GNL_FAILURE_BUFFER_SIZE)
			ft_dprintf(STDERR_FILENO,
				"pipex: get_next_line: Invalid BUFFER_SIZE\n");
		else if (return_code == GNL_FAILURE_FD)
			ft_dprintf(STDERR_FILENO,
				"pipex: get_next_line: Invalid fd\n");
		proc_err(data, EXIT_FAILURE, ERR_NOT_PRINT, NULL);
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

void	proc_here_doc(char *argv[], t_data *data)
{
	char	*new_line;
	int		gnl_return_code;

	set_here_doc_path(data);
	data->in_fd = open(data->here_doc_path, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (data->in_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, data->here_doc_path);
	data->status = STATUS_AFTER_OPEN_INFILE;
	while (1)
	{
		if (ft_dprintf(1, "> ") == -1)
			proc_err(data, EXIT_FAILURE, ERR_WRITE, NULL);
		new_line = get_next_line(STDIN_FILENO, &gnl_return_code);
		if (new_line == NULL)
		{
			if (gnl_return_code != GNL_SUCCESS_FIN)
				proc_gnl_err(data, gnl_return_code);
			else
			{
				ft_dprintf(2, "pipex: warning: here-document delimited "
					"by end-of-file (wanted `%s')\n", argv[2]);
				break ;
			}
		}
		else
		{
			if (cmp_limiter(argv[2], new_line) == 0)
			{
				free(new_line);
				break ;
			}
			else
			{
				write(data->in_fd, new_line, strlen(new_line));
				free(new_line);
			}
		}
	}
}

// It is guaranteed that argc >= 3.
void	parse_files_bonus(int argc, char *argv[], t_data *data)
{
	if (data->has_here_doc == true)
	{
		proc_here_doc(argv, data);
		if (argc == 3)
		{
			if (close(data->in_fd) == -1)
				proc_err(data, EXIT_FAILURE, ERR_CLOSE, NULL);
			if (unlink(data->here_doc_path) == -1)
				proc_err(data, EXIT_FAILURE, ERR_UNLINK, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		data->in_fd = open(argv[1], O_RDONLY);
		if (data->in_fd == -1)
			proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[1]);
	}
	data->status = STATUS_AFTER_OPEN_INFILE;
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
	if (data->out_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[argc - 1]);
	data->status = STATUS_AFTER_OPEN_OUTFILE;
}

void	parse_files(int argc, char *argv[], t_data *data)
{
	data->in_fd = open(argv[1], O_RDONLY);
	if (data->in_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[1]);
	data->status = STATUS_AFTER_OPEN_INFILE;
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
	if (data->out_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, argv[argc - 1]);
	data->status = STATUS_AFTER_OPEN_OUTFILE;
}
