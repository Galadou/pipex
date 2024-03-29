/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:21 by gmersch           #+#    #+#             */
/*   Updated: 2024/03/29 13:01:32 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**catch_path(char **envp)
{
	int		y;
	int		i;
	char	**path;

	y = 0;
	if (!envp)
	{
		ft_putstr_fd("Error pipex : Envp is empty\n", STDERR_FILENO);
		exit (1);
	}
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

static void	define_struct(t_cmd *cmd)
{
	cmd->cmd1 = NULL;
	cmd->cmd2 = NULL;
	cmd->good_path2 = NULL;
	cmd->good_path = NULL;
}

static void	open_files(t_cmd *cmd, char **argv)
{
	define_struct(cmd);
	cmd->infile = open(argv[1], O_RDONLY);
	if (cmd->infile <= 0)
	{
		if (cmd->path)
			free_tab(cmd->path);
		ft_putstr_fd("Error\nFile error (in main.c l:52)\n", STDERR_FILENO);
		exit (1);
	}
	cmd->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile <= 0)
	{
		close(cmd->infile);
		if (cmd->path)
			free_tab(cmd->path);
		ft_putstr_fd("Error\nCan't open file (main.c l:60)\n", STDERR_FILENO);
		exit (1);
	}
}

static void	create_cmd(char **argv, t_cmd *cmd)
{
	int	x;

	x = 0;
	while (argv[2][x])
	{
		if ((argv[2][x] == ' ' && argv[2][x + 1] == ' ') ||
			(argv[2][0] == ' ' || argv[2][ft_strlen(argv[2]) - 1] == ' '))
			error_free_and_exit("Error\nExtra space in command one", cmd);
		x++;
	}
	cmd->cmd1 = ft_split(argv[2], ' ');
	if (ft_strlen(cmd->cmd1[0]) == 0 || !cmd->cmd1)
		error_free_and_exit("Error\nCommand One empty or not valid", cmd);
	x = 0;
	while (argv[3][x])
	{
		if ((argv[3][x] == ' ' && argv[3][x + 1] == ' ') ||
			(argv[3][0] == ' ' || argv[3][ft_strlen(argv[3]) - 1] == ' '))
			error_free_and_exit("Error\nExtra space in command two", cmd);
		x++;
	}
	cmd->cmd2 = ft_split(argv[3], ' ');
	if (ft_strlen(cmd->cmd2[0]) == 0 || !cmd->cmd2)
		error_free_and_exit("Error\nCommand Two empty or not valid", cmd);
}

int	main(int argc, char **argv, char *envp[])
{
	t_cmd	cmd;

	if (envp == NULL)
	{
		ft_putstr_fd("Error\nCannot find envp", STDERR_FILENO);
		exit (1);
	}
	cmd.path = catch_path(envp);
	verif_arg_and_path(argc, cmd.path);
	open_files(&cmd, argv);
	create_cmd(argv, &cmd);
	cmd.good_path = path_1_creator(&cmd);
	if (!cmd.good_path)
		error_free_and_exit("Error\nCommand in main.c l:89", &cmd);
	cmd.good_path2 = path_2_creator(cmd.cmd2, cmd.good_path);
	if (!cmd.good_path2)
		error_free_and_exit("Error\nCommand in main.c l:92", &cmd);
	family_process(envp, &cmd);
	return (0);
}
