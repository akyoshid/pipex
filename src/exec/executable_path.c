/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:54:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/17 12:25:49 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

char	*set_executable_path(char *cmd, t_data *data)
{
	char	*executable_path;
	char	*env_path;
	char	**path_list;
	char	*slash_cmd;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
		return (set_executable_path_dup_cmd(cmd));
	env_path = search_var_value(data, "PATH");
	if (env_path == NULL || *env_path == '\0')
		return (set_executable_path_current_dir(cmd));
	path_list = split_env_path(env_path);
	slash_cmd = join_slash_cmd(cmd);
	i = 0;
	while (path_list[i] != NULL)
	{
		executable_path = set_executable_path_path_list_i(
				path_list, i, slash_cmd);
		if (executable_path != NULL)
			return (executable_path);
		i++;
	}
	free(slash_cmd);
	free_2d_array(path_list);
	return (NULL);
}

int	check_executable_path(char *cmd, t_data *data, char **executable_path_p)
{
	char	*env_path;

	env_path = search_var_value(data, "PATH");
	if (cmd == NULL)
	{
		if (env_path == NULL || *env_path == '\0')
			print_err(ERR_PARAM, "pipex: : command not found\n");
		else
			print_err(ERR_PARAM, "pipex: : No such file or directory\n");
		return (PIPEX_CMD_NOT_FOUND);
	}
	*executable_path_p = set_executable_path(cmd, data);
	if (*executable_path_p == NULL)
		return (print_err(ERR_CMDNOTFOUND, cmd), PIPEX_CMD_NOT_FOUND);
	if (access(*executable_path_p, X_OK) == -1)
	{
		if (env_path == NULL || *env_path == '\0')
			return (print_err(ERR_CMDNOTFOUND, cmd), free(*executable_path_p),
				PIPEX_CMD_NOT_FOUND);
		else
			return (print_err(ERR_ACCESS, cmd), free(*executable_path_p),
				PIPEX_CANNOT_EXEC);
	}
	return (0);
}
