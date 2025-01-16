/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:07:36 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/16 19:35:47 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	print_ast(t_ast *node)
{
	int	i;

	if (node == NULL)
		return ;
	print_ast(node->left);
	if (node->type == NODE_PIPE)
		ft_printf("| ");
	print_ast(node->right);
	if (node->type == NODE_COMMAND)
	{
		i = 0;
		while (node->argv[i] != NULL)
		{
			ft_printf("%s ", node->argv[i]);
			i++;
		}
	}
}

void	free_command_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	clear_ast(t_ast *node)
{
	if (node == NULL)
		return ;
	clear_ast(node->left);
	clear_ast(node->right);
	if (node->type == NODE_COMMAND)
		free_command_argv(node->argv);
	free(node);
}
