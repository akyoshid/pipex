/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:54:48 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/17 12:37:01 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	init_data(t_data *data, char *envp[])
{
	data->envp = envp;
	data->env_list = NULL;
	data->has_here_doc = false;
	data->status = STATUS_INITIAL;
}
