/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:27:48 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/16 18:33:42 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
		clear_ast(right);
		clear_ast(left);
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
	left = wrapped_parse_command(argv[i], data, NULL);
	i++;
	while (i < argc - 1)
	{
		right = wrapped_parse_command(argv[i], data, left);
		left = create_pipe(data, left, right);
		i++;
	}
	return (left);
}

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

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	init_data(&data);
	check_argc_bonus(argc, argv, &data);
	parse_envs(envp, &data);
	parse_files_bonus(argc, argv, &data);
	data.ast_root = parse_ast(argc, argv, &data);
	print_ast(data.ast_root);
	ft_printf("\n");
	// exec_ast(&data);
	exit_pipex(&data, EXIT_SUCCESS, NO_ERROR, NULL);
}
