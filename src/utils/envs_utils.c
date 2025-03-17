/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:57:24 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:17:01 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

// Find a `key` in `data->env_list` that matches `str` and return its `value`.
// `str` must be null-terminated.
char	*search_var_value(t_data *data, char *str)
{
	t_env	*current_node;

	current_node = data->env_list;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->key, str) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}

void	clear_env_list(t_data *data)
{
	t_env	*current_node;
	t_env	*next_node;

	current_node = data->env_list;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->key);
		free(current_node->value);
		free(current_node);
		current_node = next_node;
	}
	data->env_list = NULL;
}

void	print_env_list(t_data *data)
{
	t_env	*current_node;
	t_env	*next_node;

	current_node = data->env_list;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		ft_printf("%s | ", current_node->key);
		ft_printf("%s\n", current_node->value);
		current_node = next_node;
	}
}
