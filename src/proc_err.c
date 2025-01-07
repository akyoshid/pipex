/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:50:13 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/07 06:38:28 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	proc_err(int exit_status, int err_code, char *param)
{
	if (err_code == ERR_PARAM)
		ft_dprintf(2, param);
	exit(exit_status);
}
