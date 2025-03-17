/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_path_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:54:50 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:25:44 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

char	*set_executable_path_dup_cmd(char *cmd)
{
	char	*executable_path;

	executable_path = ft_strdup(cmd);
	if (executable_path == NULL)
		abort_memory_err("ft_strdup");
	return (executable_path);
}

char	*set_executable_path_current_dir(char *cmd)
{
	char	*executable_path;

	executable_path = ft_strjoin("./", cmd);
	if (executable_path == NULL)
		abort_memory_err("ft_strjoin");
	return (executable_path);
}

char	**split_env_path(char *env_path)
{
	char	**path_list;

	path_list = ft_split(env_path, ':');
	if (path_list == NULL)
		abort_memory_err("ft_split");
	return (path_list);
}

char	*join_slash_cmd(char *cmd)
{
	char	*slash_cmd;

	slash_cmd = ft_strjoin("/", cmd);
	if (slash_cmd == NULL)
		abort_memory_err("ft_strjoin");
	return (slash_cmd);
}

char	*set_executable_path_path_list_i(
	char **path_list, int i, char *slash_cmd)
{
	char	*executable_path;

	executable_path = ft_strjoin(path_list[i], slash_cmd);
	if (executable_path == NULL)
		abort_memory_err("ft_strjoin");
	if (access(executable_path, F_OK) == 0)
	{
		free(slash_cmd);
		free_2d_array(path_list);
		return (executable_path);
	}
	free(executable_path);
	return (NULL);
}
