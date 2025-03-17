/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:07:49 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:44:28 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

t_ast	*create_node(t_node_type type)
{
	t_ast	*tmp;

	tmp = (t_ast *)xmalloc(sizeof(t_ast) * 1);
	tmp->type = type;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->argv = NULL;
	tmp->redir_in_flag = false;
	tmp->redir_out_flag = false;
	tmp->here_doc_flag = false;
	tmp->redir_in_path = NULL;
	tmp->redir_out_path = NULL;
	tmp->here_doc_word = NULL;
	ft_bzero((void *)tmp->here_doc_path, 23);
	return (tmp);
}

static t_ast	*_create_command(int argc, char *argv[], t_data *data, int i)
{
	t_ast	*tmp;

	tmp = create_node(NODE_COMMAND);
	tmp->argv = ft_split_mult_c(argv[i], " \n\t");
	if (tmp->argv == NULL)
		abort_memory_err("ft_split_mult_c");
	if (data->has_here_doc == false && i == 2)
	{
		tmp->redir_in_flag = true;
		tmp->redir_in_path = argv[1];
	}
	else if (data->has_here_doc == true && i == 3)
	{
		tmp->here_doc_flag = true;
		tmp->here_doc_word = argv[2];
	}
	if (i == argc - 2)
	{
		tmp->redir_out_flag = true;
		tmp->redir_out_path = argv[argc - 1];
	}
	return (tmp);
}

static t_ast	*_create_pipe(t_ast *left, t_ast *right)
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
		left = _create_command(argc, argv, data, i);
		i++;
		while (i < argc - 1)
		{
			right = _create_command(argc, argv, data, i);
			left = _create_pipe(left, right);
			i++;
		}
		return (left);
	}
	else
		return (NULL);
}
