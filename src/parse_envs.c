/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:55:54 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/11 15:48:59 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_env	*malloc_env(void)
{
	t_env	*buff;

	buff = malloc(1 * sizeof(t_env));
	if (buff == NULL)
		return (NULL);
	buff->key = NULL;
	buff->value = NULL;
	buff->next = NULL;
	return (buff);
}

void	add_back_env(t_data *data, t_env *new)
{
	t_env	*current_node;

	if (data->env_list == NULL)
	{
		data->env_list = new;
		return ;
	}
	current_node = data->env_list;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new;
}

void	parse_envs(char *envp[], t_data *data)
{
	int		i;
	char	*equal_p;
	t_env	*new_node;

	data->status = STATUS_MALLOC_ENVS;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = malloc_env();
		if (new_node == NULL)
			exit_pipex(data, EXIT_FAILURE, ERR_MALLOC, NULL);
		add_back_env(data, new_node);
		equal_p = ft_strchr(envp[i], '=');
		new_node->key = (char *)malloc(sizeof(char) * (equal_p - envp[i] + 1));
		if (new_node->key == NULL)
			exit_pipex(data, EXIT_FAILURE, ERR_MALLOC, NULL);
		new_node->value = (char *)malloc(
				sizeof(char) * (ft_strlen(envp[i]) - (equal_p - envp[i])));
		if (new_node->value == NULL)
			exit_pipex(data, EXIT_FAILURE, ERR_MALLOC, NULL);
		ft_strlcpy(new_node->key, envp[i], equal_p - envp[i] + 1);
		ft_strlcpy(new_node->value,
			equal_p + 1, ft_strlen(envp[i]) - (equal_p - envp[i]));
		i++;
	}
}
