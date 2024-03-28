/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:48 by gmersch           #+#    #+#             */
/*   Updated: 2024/03/27 16:51:46 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}

void	ultimate_free(t_cmd *cmd)
{
	close(cmd->infile);
	close(cmd->outfile);
	if (cmd->path)
		free_tab(cmd->path);
	if (cmd->cmd1)
		free_tab(cmd->cmd1);
	if (cmd->cmd2)
		free_tab(cmd->cmd2);
	if (cmd->good_path)
		free(cmd->good_path);
	if (cmd->good_path2)
		free(cmd->good_path2);
}
