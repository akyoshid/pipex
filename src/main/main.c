/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:17:57 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 11:43:51 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		exit_status;

	init_data(&data, envp);
	check_argc(argc, &data);
	parse_envs(envp, &data);
	data.ast_root = parse_ast(argc, argv, &data);
	exit_status = exec_ast(data.ast_root, &data);
	exit_pipex(&data, exit_status, NO_ERROR, NULL);
}
