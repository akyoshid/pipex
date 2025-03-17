/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_limiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:00:43 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 11:41:53 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

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
