/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:08:18 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/11 17:42:19 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	verif_arg_and_path(int argc, char **path, t_cmd *cmd)
{
	if (argc != 5)
	{
		free_tab(path);
		ft_putstr_fd("Error\nNot good number of arg\n", STDERR_FILENO);
		if (cmd->infile != -1)
			close(cmd->infile);
		if (cmd->outfile != -1)
			close(cmd->outfile);
		exit (1);
	}
	if (!path)
		free_tab(path);
}

void	error_free_and_exit(char *error, t_cmd *cmd)
{
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	ultimate_free(cmd);
	exit (1);
}
