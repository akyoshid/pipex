/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:07:49 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/16 19:36:56 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// If malloc fails, output the error message to standard error and return NULL.
t_ast	*create_node(t_node_type type)
{
	t_ast	*tmp;

	tmp = (t_ast *)malloc(sizeof(t_ast) * 1);
	if (tmp == NULL)
	{
		print_err(ERR_MALLOC, NULL);
		return (NULL);
	}
	tmp->type = type;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->argv = NULL;
	return (tmp);
}

t_ast	*parse_command(char *arg)
{
	t_ast	*tmp;

	tmp = create_node(NODE_COMMAND);
	if (tmp == NULL)
		return (NULL);
	tmp->argv = ft_split_mult_c(arg, " \n\t");
	if (tmp->argv == NULL)
	{
		print_err(ERR_MALLOC, NULL);
		free(tmp);
		return (NULL);
	}
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

t_ast	*wrapped_parse_command(char *arg, t_data *data, t_ast *root)
{
	t_ast	*tmp;

	tmp = parse_command(arg);
	if (tmp == NULL)
	{
		clear_ast(root);
		exit_pipex(data, EXIT_FAILURE, ERR_NOT_PRINT, NULL);
	}
	return (tmp);
}

t_ast	*create_pipe(t_data *data, t_ast *left, t_ast *right)
{
	t_ast	*tmp;

	tmp = create_node(NODE_PIPE);
	if (tmp == NULL)
	{
		clear_ast(left);
		clear_ast(right);
		exit_pipex(data, EXIT_FAILURE, ERR_NOT_PRINT, NULL);
	}
	tmp->left = left;
	tmp->right = right;
	return (tmp);
}

t_ast	*parse_ast(int argc, char *argv[], t_data *data)
{
	int	i;
	t_ast	*left;
	t_ast	*right;

	i = 2;
	if (data->has_here_doc == true)
		i = 3;
	if (i < argc - 1)
	{
		left = wrapped_parse_command(argv[i], data, NULL);
		i++;
		while (i < argc - 1)
		{
			right = wrapped_parse_command(argv[i], data, left);
			left = create_pipe(data, left, right);
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
