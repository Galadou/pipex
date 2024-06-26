/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:08:36 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/20 16:17:49 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	family_process(char **envp, t_cmd *cmd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		error_free_and_exit("Error\nPipe in process_family.c\n", cmd, pipefd);
	if (cmd->cmd1_error == 0 && cmd->file1_error == 0)
	{
		pid = fork();
		if (pid == -1)
			error_free_and_exit("Error\nFork at process_family.c\n", \
				cmd, pipefd);
		else if (pid == 0)
			first_child(pipefd, cmd, envp);
		else
			process_parent(pipefd, cmd, envp);
	}
	else
		process_parent(pipefd, cmd, envp);
}

void	process_parent(int pipefd[2], t_cmd *cmd, char **envp)
{
	pid_t	pid;

	if (cmd->cmd2_error == 0 && cmd->file2_error == 0)
	{
		pid = fork();
		if (pid == -1)
			error_free_and_exit("Error\nFork at process_parent.c\n", \
				cmd, pipefd);
		else if (pid == 0)
			second_child(pipefd, cmd, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
	ultimate_free(cmd, pipefd);
}
