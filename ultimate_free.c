/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:48 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/20 16:13:48 by gmersch          ###   ########.fr       */
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

void	ultimate_free(t_cmd *cmd, int pipefd[2])
{
	if (pipefd[0])
		close(pipefd[0]);
	if (pipefd[1])
		close(pipefd[1]);
	if (cmd->infile != -1 && cmd->infile)
		close(cmd->infile);
	if (cmd->outfile != -1 && cmd->outfile)
		close(cmd->outfile);
	if (cmd->path || cmd->path != NULL)
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
