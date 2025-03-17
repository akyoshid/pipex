/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:01:33 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:25:23 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int	exec_ast(t_ast *node, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (node == NULL)
		return (PIPEX_SUCCESS);
	if (node->type == NODE_COMMAND)
		exit_status = exec_command(node, data);
	else if (node->type == NODE_PIPE)
		exit_status = exec_pipe(node, data);
	return (exit_status);
}
