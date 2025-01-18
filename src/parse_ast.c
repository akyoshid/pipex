/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:07:49 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/18 19:39:48 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_ast	*create_node(t_node_type type)
{
	t_ast	*tmp;

	tmp = (t_ast *)xmalloc(sizeof(t_ast) * 1);
	tmp->type = type;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->argv = NULL;
	tmp->redir_in = false;
	tmp->redir_out = false;
	return (tmp);
}

t_ast	*parse_command(char *arg, int i, int argc, t_data *data)
{
	t_ast	*tmp;

	tmp = create_node(NODE_COMMAND);
	tmp->argv = ft_split_mult_c(arg, " \n\t");
	if (tmp->argv == NULL)
		abort_memory_err("ft_split_mult_c");
	if ((data->has_here_doc == false && i == 2)
		|| (data->has_here_doc == true && i == 3))
		tmp->redir_in = data->in_fd;
	if (i == argc - 2)
		tmp->redir_out = data->out_fd;
	return (tmp);
}

t_ast	*create_pipe(t_ast *left, t_ast *right)
{
	t_ast	*tmp;

	tmp = create_node(NODE_PIPE);
	tmp->left = left;
	tmp->right = right;
	return (tmp);
}

t_ast	*parse_ast(int argc, char *argv[], t_data *data)
{
	int		i;
	t_ast	*left;
	t_ast	*right;

	i = 2;
	if (data->has_here_doc == true)
		i = 3;
	if (i < argc - 1)
	{
		left = parse_command(argv[i], i, argc, data);
		i++;
		while (i < argc - 1)
		{
			right = parse_command(argv[i], i, argc, data);
			left = create_pipe(left, right);
			i++;
		}
		data->status = STATUS_PARSE_AST;
		return (left);
	}
	else
	{
		data->status = STATUS_PARSE_AST;
		return (NULL);
	}
}
