/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:24 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 11:42:20 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	exit_pipex(t_data *data, int exit_status, int err_code, char *param)
{
	print_err(err_code, param);
	clear_ast(data->ast_root);
	clear_env_list(data);
	exit(exit_status);
}
