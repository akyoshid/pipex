/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:27:48 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/17 12:44:08 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	init_data(&data, envp);
	check_argc_bonus(argc, argv, &data);
	parse_envs(envp, &data);
	parse_files_bonus(argc, argv, &data);
	data.ast_root = parse_ast(argc, argv, &data);
	//
	print_ast(data.ast_root);
	ft_printf("\n");
	//
	// exec_ast(&data);
	exit_pipex(&data, EXIT_SUCCESS, NO_ERROR, NULL);
}
