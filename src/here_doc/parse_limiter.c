/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_limiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:03:36 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 11:42:10 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

static void	_parse_limiter_quotation(
	char *limiter, t_heredoc *hd_data, int i, int len)
{
	i = 0;
	while (limiter[i] != '\0')
	{
		if (hd_data->in_quotation == true
			&& ((hd_data->single_quote == true && limiter[i] == '\'')
				|| (hd_data->single_quote == false && limiter[i] == '\"')))
		{
			hd_data->in_quotation = false;
			ft_strlcpy(limiter + i, limiter + i + 1, len - i + 1);
		}
		else if (hd_data->in_quotation == false
			&& (limiter[i] == '\'' || limiter[i] == '\"'))
		{
			hd_data->quoted_limiter = true;
			hd_data->in_quotation = true;
			if (limiter[i] == '\'')
				hd_data->single_quote = true;
			else
				hd_data->single_quote = false;
			ft_strlcpy(limiter + i, limiter + i + 1, len - i + 1);
		}
		else
			i++;
	}
}

int	parse_limiter(char *limiter, t_heredoc *hd_data)
{
	hd_data->leading_hyphen = false;
	if (limiter[0] == '-')
	{
		hd_data->leading_hyphen = true;
		ft_strlcpy(limiter, limiter + 1, ft_strlen(limiter) + 1);
	}
	hd_data->quoted_limiter = false;
	hd_data->in_quotation = false;
	hd_data->single_quote = false;
	_parse_limiter_quotation(limiter, hd_data, 0, ft_strlen(limiter));
	if (hd_data->in_quotation == true)
	{
		if (hd_data->single_quote == true)
			print_err(ERR_PARAM,
				"pipex: syntax error: unclosed single quote\n");
		else
			print_err(ERR_PARAM,
				"pipex: syntax error: unclosed double quote\n");
		return (-1);
	}
	hd_data->limiter = limiter;
	return (0);
}
