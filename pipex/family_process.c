/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:57 by gmersch           #+#    #+#             */
/*   Updated: 2024/03/29 12:09:24 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int pipefd[2], t_cmd *cmd, char **envp)
{
	dup2(cmd->infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(cmd->good_path, cmd->cmd1, envp);
	ultimate_free(cmd);
	perror("First exec");
}

static void	child_process2(int pipefd[2], t_cmd *cmd, char **envp)
{
	dup2(cmd->outfile, STDOUT_FILENO);
	execve(cmd->good_path2, cmd->cmd2, envp);
	if (pipefd[0])
		close(pipefd[0]);
	if (pipefd[1])
		close(pipefd[1]);
	ultimate_free(cmd);
	perror("Second exec");
}

static void	family_process_end(t_cmd *cmd, int pipefd[2])
{
	wait(NULL);
	close(pipefd[1]);
	ultimate_free(cmd);
}

void	family_process(char **envp, t_cmd *cmd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		error_free_and_exit("Error\nPipe in family_process.c l:61\n", cmd);
	pid = fork();
	if (pid == -1)
		error_free_and_exit("Error\nFork at family_process.c l:63\n", cmd);
	else if (pid == 0)
		child_process(pipefd, cmd, envp);
	else
	{
		wait(NULL);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		pid = fork();
		if (pid == -1)
			error_free_and_exit("Error\nFork at family_process.c l:74\n", cmd);
		else if (pid == 0)
			child_process2(pipefd, cmd, envp);
		else
			family_process_end(cmd, pipefd);
	}
}
