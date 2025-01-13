/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:48:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/13 15:01:09 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	calc_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
	{
		i = 1;
		if (ft_isalpha(str[1]) == 1 || str[1] == '_')
		{
			i = 2;
			while (ft_isalnum(str[i]) == 1 || str[i] == '_')
				i++;
		}
	}
	return (i);
}

// Find a `key` in `data->env_list` that matches `str` and return its `value`.
// `str` must be null-terminated.
char	*search_var_value(t_data *data, char *str)
{
	t_env *current_node;

	current_node = data->env_list;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->key, str) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}

char	*here_doc_expand_var(t_data *data, char *src)
{
	int		i;
	int		var_len;
	char	temp;
	char	*var_value;
	char	*new;

	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '$')
		{
			var_len = calc_var_len(src + i);
			temp = src[i + var_len];
			src[i + var_len] = '\0';
			var_value = search_var_value(data, src + i + 1);
			src[i + var_len] = temp;
			if (var_value == NULL)
				ft_strlcpy(src + i, src + i + var_len, ft_strlen(src) - i + 1);
			else
			{
				new = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1 - var_len + ft_strlen(var_value)));
				if (new == NULL)
				{
					free(src);
					exit_pipex(data, EXIT_FAILURE, ERR_MALLOC, NULL);
				}
				ft_strncpy(new, src, i);
				ft_strncpy(new + i, var_value, ft_strlen(var_value));
				ft_strlcpy(new + i + ft_strlen(var_value), src + i + var_len, (ft_strlen(src) + 1 - var_len - i));
				free(src);
				src = new;
			}
		}
		else
			i++;
	}
	return (src);
}

void	here_doc_delete_tab(char *new_line)
{
	int		count;

	count = 0;
	while (new_line[count] == '\t')
		count++;
	if (count > 0)
		ft_strlcpy(new_line, new_line + count, ft_strlen(new_line) + 1);
}

bool	here_doc_error(t_data *data, int gnl_return_code, t_heredoc *hd_data)
{
	if (gnl_return_code != GNL_SUCCESS_FIN)
		proc_gnl_err(data, gnl_return_code);
	else
		ft_dprintf(2, "\npipex: warning: here-document delimited "
			"by end-of-file (wanted `%s')\n", hd_data->limiter);
	return (false);
}

bool	here_doc_success(t_data *data, char *new_line, t_heredoc *hd_data)
{
	if (hd_data->leading_hyphen == true)
		here_doc_delete_tab(new_line);
	if (cmp_limiter(hd_data->limiter, new_line) == 0)
	{
		free(new_line);
		return (false);
	}
	else
	{
		if (hd_data->quoted_limiter == false)
			new_line = here_doc_expand_var(data, new_line);
		if (write(data->in_fd, new_line, ft_strlen(new_line)) == -1)
		{
			free(new_line);
			exit_pipex(data, EXIT_FAILURE, ERR_WRITE, NULL);
		}
		free(new_line);
		return (true);
	}
}

void	proc_here_doc(char *argv[], t_data *data)
{
	t_heredoc	hd_data;
	bool		loop_flag;
	char		*new_line;
	int			gnl_return_code;

	set_here_doc_path(data);
	data->in_fd = open(data->here_doc_path, O_CREAT | O_EXCL | O_WRONLY, 0666);
	if (data->in_fd == -1)
		exit_pipex(data, EXIT_FAILURE, ERR_OPEN, data->here_doc_path);
	data->status = STATUS_OPEN_INFILE;
	parse_limiter(data, argv[2], &hd_data);
	loop_flag = true;
	while (loop_flag)
	{
		if (ft_dprintf(1, "> ") == -1)
			exit_pipex(data, EXIT_FAILURE, ERR_WRITE, NULL);
		new_line = get_next_line(STDIN_FILENO, &gnl_return_code);
		if (new_line == NULL)
			loop_flag = here_doc_error(data, gnl_return_code, &hd_data);
		else
			loop_flag = here_doc_success(data, new_line, &hd_data);
	}
	close_and_open_here_doc_file(data);
	print_here_doc(data);
}
