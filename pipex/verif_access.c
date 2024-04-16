/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:33 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/16 14:41:07 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*verif_access(char *cmd, char **path, int i)
{
	char	*good_path;
	char	*path_buf;

	if (is_only_slash(cmd) == 0)
	{
		if (path[i][ft_strlen(path[i])] != '/')
			path_buf = ft_strjoin(path[i], "/");
		good_path = ft_strjoin(path_buf, cmd);
		if (access(good_path, X_OK) == 0)
		{
			free(path_buf);
			return (good_path);
		}
		free(path_buf);
		free(good_path);
	}
	return (0);
}

void	path_error(t_cmd *cmd, char *good_path)
{
	if (good_path)
		free(good_path);
	cmd->cmd1_error = 1;
}

static char	*cmd_is_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*path_1_creator(t_cmd *cmd)
{
	int		i;
	char	*good_path;

	i = 0;
	good_path = NULL;
	if (access(cmd->cmd1[0], X_OK) == 0 && is_only_slash(cmd->cmd1[0]) == 0)
		good_path = cmd_is_path(cmd->cmd1[0]);
	if (good_path == NULL && cmd->path)
	{
		while (cmd->path[i] && (!good_path))
		{
			if (good_path)
				free(good_path);
			good_path = verif_access(cmd->cmd1[0], cmd->path, i);
			if (good_path)
				return (good_path);
			i++;
		}
		path_error(cmd, good_path);
	}
	else
		cmd->gp_not_malloc = 1;
	return (good_path);
}

char	*path_2_creator(t_cmd *cmd)
{
	int		i;
	char	*good_path;

	i = 0;
	good_path = NULL;
	if (access(cmd->cmd2[0], X_OK) == 0 && is_only_slash(cmd->cmd2[0]) == 0)
		good_path = cmd_is_path(cmd->cmd2[0]);
	if (good_path == NULL && cmd->path)
	{
		while (cmd->path[i] && (!good_path))
		{
			good_path = verif_access(cmd->cmd2[0], cmd->path, i);
			if (good_path)
				return (good_path);
			i++;
		}
		if (good_path)
			free(good_path);
		error_free_and_exit("Error\nCommand two does not exist\n", cmd);
	}
	else
		cmd->gp2_not_malloc = 1;
	return (good_path);
}
