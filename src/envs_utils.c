/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:57:24 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 08:57:53 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
