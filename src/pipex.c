/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:17:57 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/10 19:27:31 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	init_data(&data);
	check_argc(argc, &data);
	parse_envs(envp, &data);
	parse_files(argc, argv, &data);
	// parse_cmds(argc, argv, envp, &data);
	// parse_args(argc, argv, envp, &data);
	(void)envp;
	exit_pipex(&data, EXIT_SUCCESS, NO_ERROR, NULL);
}
