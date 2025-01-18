/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:16:02 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/18 17:25:35 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	calc_var_key_len(char *str)
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

char	*replace_by_var_value(
	char *src, int *i, int var_key_len, char *var_value)
{
	char	*new;
	int		src_len;
	int		var_value_len;

	src_len = ft_strlen(src);
	if (var_value == NULL)
	{
		ft_strlcpy(src + *i, src + *i + var_key_len, src_len - *i + 1);
		return (src);
	}
	else
	{
		var_value_len = ft_strlen(var_value);
		new = (char *)xmalloc(
				sizeof(char) * (src_len + 1 - var_key_len + var_value_len));
		ft_strncpy(new, src, *i);
		ft_strncpy(new + *i, var_value, var_value_len);
		ft_strlcpy(new + *i + var_value_len,
			src + *i + var_key_len, (src_len + 1 - var_key_len - *i));
		free(src);
		*i += var_value_len;
		return (new);
	}
}

char	*here_doc_expand_var(t_data *data, char *src)
{
	int		i;
	int		var_key_len;
	char	temp;
	char	*var_value;

	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '$')
		{
			var_key_len = calc_var_key_len(src + i);
			temp = src[i + var_key_len];
			src[i + var_key_len] = '\0';
			var_value = search_var_value(data, src + i + 1);
			src[i + var_key_len] = temp;
			src = replace_by_var_value(src, &i, var_key_len, var_value);
		}
		else
			i++;
	}
	return (src);
}
