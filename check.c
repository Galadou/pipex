/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:08:18 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/20 16:15:07 by gmersch          ###   ########.fr       */
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

void	error_free_and_exit(char *error, t_cmd *cmd, int pipefd[2])
{
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	ultimate_free(cmd, pipefd);
	exit (1);
}

static size_t	count_slash(char *str)
{
	size_t	nb_slash;
	int		i;

	i = 0;
	nb_slash = 0;
	while (str[i])
	{
		if (str[i] == '/')
			nb_slash++;
		i++;
	}
	return (nb_slash);
}

int	is_only_slash(char *str, int c, t_cmd *cmd)
{
	size_t	i;
	size_t	nb_slash;

	i = 0;
	nb_slash = count_slash(str);
	if (str[0] == '/')
	{
		i = 0;
		while (str[i] == '/')
			i++;
		if (i == ft_strlen(str) || (i > 0 && i == nb_slash) || \
			str[ft_strlen(str) - 1] == '/')
		{
			if (c == 1)
				cmd->cmd1_error = 1;
			if (c == 2)
				cmd->cmd2_error = 1;
			return (1);
		}
	}
	return (0);
}

void	path_creator(t_cmd *cmd)
{
	if (cmd->cmd1_error == 0)
	{
		cmd->good_path = path_1_creator(cmd);
		if (!cmd->good_path)
		{
			if (cmd->file1_error == 0)
				ft_putstr_fd("Error\nCommand one not valid\n", STDERR_FILENO);
			cmd->cmd1_error = 1;
		}
	}
	if (cmd->cmd2_error == 0)
	{
		cmd->good_path2 = path_2_creator(cmd);
		if (!cmd->good_path2)
		{
			if (cmd->file2_error == 0)
				ft_putstr_fd("Error\nCommand two not valid\n", STDERR_FILENO);
			cmd->cmd2_error = 1;
		}
	}
}
