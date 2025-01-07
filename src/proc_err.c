/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:50:13 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/07 05:50:48 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	proc_err(int err_code, char *param)
{
	if (err_code == ERR_PARAM)
		ft_dprintf(2, param);
	exit(EXIT_FAILURE);
}
