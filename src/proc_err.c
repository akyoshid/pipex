/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:50:13 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/07 09:49:58 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	proc_err(int exit_status, int err_code, char *param)
{
	if (err_code == ERR_PARAM)
		ft_dprintf(2, param);
	else if (err_code == ERR_OPEN)
		ft_dprintf(2, "pipex: %s: %s\n", param, strerror(errno));
	exit(exit_status);
}
