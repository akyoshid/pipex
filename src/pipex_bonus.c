/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:27:48 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 19:33:20 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	init_data(&data);
	check_argc_bonus(argc, argv, &data);
	parse_envs(envp, &data);
	parse_files_bonus(argc, argv, &data);
	// parse_cmds(argc, argv, envp, &data);
	// parse_args(argc, argv, envp, &data);
	(void)envp;
	exit_pipex(&data, EXIT_SUCCESS, NO_ERROR, NULL);
}
