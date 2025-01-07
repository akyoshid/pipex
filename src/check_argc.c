/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:49:34 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/07 06:09:29 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	check_argc(int argc)
{
	if (argc != 5)
	{
		proc_err(EXIT_FAILURE, ERR_PARAM,
			"pipex: Invalid number of arguments\n"
			"Usage: pipex infile cmd1 cmd2 outfile\n");
	}
}
