/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:48 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/05 11:03:37 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	y;

	y = 0;
	if (tab != NULL)
	{
		while (tab[y])
		{
			free(tab[y]);
			y++;
		}
		free(tab);
	}
}

void	ultimate_free(t_cmd *cmd)
{
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	if (cmd->path && cmd->path != NULL)
		free_tab(cmd->path);
	if (cmd->cmd1)
		free_tab(cmd->cmd1);
	if (cmd->cmd2)
		free_tab(cmd->cmd2);
	if (cmd->good_path && cmd->gp_not_malloc == 0)
		free(cmd->good_path);
	if (cmd->good_path2 && cmd->gp2_not_malloc == 0)
		free(cmd->good_path2);
}
