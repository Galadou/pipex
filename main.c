/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:21 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/20 17:12:08 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**catch_path(char **envp)
{
	int		y;
	int		i;
	char	**path;

	y = 0;
	path = NULL;
	i = 0;
	while (envp[y] != NULL)
	{
		if (envp[y][0] == 'P')
			if (envp[y][1] == 'A')
				if (envp[y][2] == 'T')
					if (envp[y][3] == 'H')
						if (envp[y][4] == '=')
							path = ft_split(&envp[y][i] + 5, ':');
		y++;
	}
	return (path);
}

static void	open_files(t_cmd *cmd, char **argv, int argc)
{
	init_struct(cmd);
	if (argc == 5)
	{
		cmd->infile = open(argv[1], O_RDONLY);
		if (cmd->infile <= 0)
		{
			ft_putstr_fd("Error\nInfile error\n", STDERR_FILENO);
			cmd->file1_error = 1;
		}
		cmd->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->outfile <= 0)
		{
			ft_putstr_fd("Error\nOutfile error\n", STDERR_FILENO);
			cmd->file2_error = 1;
		}
	}
	else
	{
		cmd->infile = -1;
		cmd->outfile = -1;
	}
}

static void	create_cmd_next(char **argv, t_cmd *cmd)
{
	int	x;

	x = 0;
	while (argv[3][x] && cmd->cmd2_error == 0)
	{
		if (argv[3][0] == ' ' || argv[3][ft_strlen(argv[3]) - 1] == ' ')
		{
			if (cmd->file2_error == 0)
				ft_putstr_fd("Error\nExtra space in cmd two\n", STDERR_FILENO);
			cmd->cmd2_error = 1;
		}
		x++;
	}
	cmd->cmd2 = ft_split(argv[3], ' ');
	if (ft_strlen(cmd->cmd2[0]) == 0 || !cmd->cmd2)
	{
		if (cmd->file2_error == 0 && cmd->cmd2_error == 0)
			ft_putstr_fd("Error\nCmd Two empty or not valid\n", STDERR_FILENO);
		cmd->cmd2_error = 1;
	}
}

static void	create_cmd(char **argv, t_cmd *cmd)
{
	int	x;

	x = 0;
	cmd->cmd1_error = 0;
	cmd->cmd2_error = 0;
	while (argv[2][x] && cmd->cmd1_error == 0)
	{
		if ((argv[2][0] == ' ' || argv[2][ft_strlen(argv[2]) - 1] == ' '))
		{
			if (cmd->file1_error == 0)
				ft_putstr_fd("Error\nExtra space in cmd one\n", STDERR_FILENO);
			cmd->cmd1_error = 1;
		}
		x++;
	}
	cmd->cmd1 = ft_split(argv[2], ' ');
	if (ft_strlen(cmd->cmd1[0]) == 0 || !cmd->cmd1)
	{
		if (cmd->file1_error == 0 && cmd->cmd1_error == 0)
			ft_putstr_fd("Error\nCmd One empty or not valid\n", STDERR_FILENO);
		cmd->cmd1_error = 1;
	}
	create_cmd_next(argv, cmd);
}

int	main(int argc, char **argv, char *envp[])
{
	t_cmd	cmd;

	if (envp == NULL)
	{
		ft_putstr_fd("Error\nCannot find envp\n", STDERR_FILENO);
		exit (1);
	}
	open_files(&cmd, argv, argc);
	cmd.path = catch_path(envp);
	verif_arg_and_path(argc, cmd.path, &cmd);
	create_cmd(argv, &cmd);
	path_creator(&cmd);
	family_process(envp, &cmd);
	return (0);
}
