/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:33 by gmersch           #+#    #+#             */
/*   Updated: 2024/03/28 10:15:54 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*verif_access(char *cmd, char **path, int i)
{
	char	*good_path;
	char	*path_buf;

	if (path[i][ft_strlen(path[i])] != '/')
		path_buf = ft_strjoin(path[i], "/");
	good_path = ft_strjoin(path_buf, cmd);
	if (access(good_path, F_OK) == 0)
	{
		free(path_buf);
		return (good_path);
	}
	free(path_buf);
	free(good_path);
	return (0);
}

void	path_error(t_cmd *cmd, char *good_path, char *good_path_buf)
{
	if (good_path)
		free(good_path);
	if (good_path_buf)
		free(good_path_buf);
	error_free_and_exit("Error\nCommand does not exist\n", cmd);
}

char	*path_1_creator(t_cmd *cmd)
{
	int		i;
	int		c;
	char	*good_path;
	char	*good_path_buf;

	i = 0;
	c = 0;
	good_path = NULL;
	while (cmd->path[i] && c == 0)
	{
		if (good_path)
			free(good_path);
		good_path = verif_access(cmd->cmd1[0], cmd->path, i);
		good_path_buf = verif_access(cmd->cmd2[0], cmd->path, i);
		if (good_path_buf)
			c++;
		if (c == 1)
		{
			free(good_path_buf);
			return (good_path);
		}
		i++;
	}
	path_error(cmd, good_path, good_path_buf);
	return (0);
}

char	*path_2_creator(char **cmd2, char *good_path)
{
	char	*good_path2;
	char	*good_path2_buf;
	int		i;

	i = ft_strlen(good_path);
	while (good_path[i] != '/')
		i--;
	i++;
	good_path2_buf = ft_substr(good_path, 0, i);
	good_path2 = ft_strjoin(good_path2_buf, cmd2[0]);
	free(good_path2_buf);
	return (good_path2);
}
