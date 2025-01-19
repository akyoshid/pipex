/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/19 15:08:16 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	here_doc_error(int gnl_return_code, t_heredoc *hd_data)
{
	if (gnl_return_code != GNL_SUCCESS_FIN)
		return (proc_gnl_err(gnl_return_code));
	else
	{
		ft_dprintf(2, "\npipex: warning: here-document delimited "
			"by end-of-file (wanted `%s')\n", hd_data->limiter);
		return (0);
	}
}

int	here_doc_success(t_data *data, char *new_line, t_heredoc *hd_data)
{
	if (hd_data->leading_hyphen == true)
		here_doc_delete_tab(new_line);
	if (cmp_limiter(hd_data->limiter, new_line) == 0)
	{
		free(new_line);
		return (0);
	}
	else
	{
		if (hd_data->quoted_limiter == false)
			new_line = here_doc_expand_var(data, new_line);
		if (write(hd_data->fd, new_line, ft_strlen(new_line)) == -1)
		{
			free(new_line);
			print_err(ERR_WRITE, NULL);
			return (-1);
		}
		free(new_line);
		return (1);
	}
}

int	proc_here_doc(t_ast *node, t_data *data)
{
	t_heredoc	hd_data;
	int			loop_flag;
	char		*new_line;
	int			gnl_return_code;

	if (set_here_doc_path(node) == -1)
		return (-1);
	hd_data.fd = open(node->here_doc_path, O_CREAT | O_EXCL | O_WRONLY, 0666);
	if (hd_data.fd == -1)
		return (print_err(ERR_OPEN, node->here_doc_path), -1);
	if (parse_limiter(node->here_doc_word, &hd_data) == -1)
		return (close(hd_data.fd), -1);
	loop_flag = 1;
	while (loop_flag == 1)
	{
		ft_dprintf(2, "> ");
		new_line = get_next_line(STDIN_FILENO, &gnl_return_code);
		if (new_line == NULL)
			loop_flag = here_doc_error(gnl_return_code, &hd_data);
		else
			loop_flag = here_doc_success(data, new_line, &hd_data);
	}
	return (close(hd_data.fd), loop_flag);
}
