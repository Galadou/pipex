/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:08:36 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/04 16:28:45 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_parent(int pipefd[2], t_cmd *cmd, char **envp)
{
	pid_t	pid;

	wait(NULL);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error", cmd);
	close(pipefd[0]);
	pid = fork();
	if (pid == -1)
		error_free_and_exit("Error\nFork at family_process.c l:74\n", cmd);
	else if (pid == 0)
		child_process2(pipefd, cmd, envp);
	else
		family_process_end(cmd, pipefd);
}

void	process_parent_cmd1_error(int pipefd[2], t_cmd *cmd, char **envp)
{
	pid_t	pid;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error", cmd);
	close(pipefd[0]);
	pid = fork();
	if (pid == -1)
		error_free_and_exit("Error\nFork at family_process.c l:74\n", cmd);
	else if (pid == 0)
		child_process2(pipefd, cmd, envp);
	else
		family_process_end(cmd, pipefd);
}
