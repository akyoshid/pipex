/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:17:57 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/16 19:39:58 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	init_data(&data, envp);
	check_argc(argc, &data);
	parse_envs(envp, &data);
	parse_files(argc, argv, &data);
	data.ast_root = parse_ast(argc, argv, &data);
	//
	print_ast(data.ast_root);
	ft_printf("\n");
	//
	// exec_ast(&data);
	exit_pipex(&data, EXIT_SUCCESS, NO_ERROR, NULL);
}
