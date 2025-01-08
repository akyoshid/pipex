/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:08 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/08 18:38:52 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

# define RAND_SUCCESS 0
# define RAND_ERR_OPEN -1
# define RAND_ERR_READ -2
# define RAND_ERR_INVALID_LEN -3

// if it is successful, return 0
// if open() fails, return -1
// if read() fails, return -2
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
	if (read_rv != len)
		return (RAND_ERR_READ);
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
	if (rand_rv == RAND_ERR_READ)
		proc_err(data, EXIT_FAILURE, ERR_READ, "/dev/urandom");
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

void	proc_here_doc(char *argv[], t_data *data)
{
	set_here_doc_path(data);
	data->in_fd = open(data->here_doc_path, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (data->in_fd == -1)
		proc_err(data, EXIT_FAILURE, ERR_OPEN, data->here_doc_path);
	data->status = STATUS_AFTER_OPEN_INFILE;
	ft_printf("%s\n", data->here_doc_path);
	(void)argv;
}

// It is guaranteed that argc >= 3.
void	parse_files_bonus(int argc, char *argv[], t_data *data)
{
	if (data->has_here_doc == true)
	{
		proc_here_doc(argv, data);
		if (argc == 3)
		{
			close(data->in_fd);
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
