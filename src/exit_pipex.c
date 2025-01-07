/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:24 by akyoshid          #+#    #+#             */
/*   Updated: 2025/01/07 15:51:00 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exit_pipex(t_data *data)
{
	close(data->in_fd);
	close(data->out_fd);
	// if (data->has_here_doc == true)
	// 	remove_here_doc_file();
}
