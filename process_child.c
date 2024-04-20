/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:02:35 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/20 16:13:32 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int pipefd[2], t_cmd *cmd, char **envp)
{
	if (pipefd[0])
		close(pipefd[0]);
	if (dup2(cmd->infile, STDIN_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error\n", cmd, pipefd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error\n", cmd, pipefd);
	if (pipefd[1])
		close(pipefd[1]);
	if (cmd->infile != -1 && cmd->infile)
		close(cmd->infile);
	if (cmd->outfile != -1 && cmd->outfile)
		close(cmd->outfile);
	execve(cmd->good_path, cmd->cmd1, envp);
	ultimate_free(cmd, pipefd);
	perror("Error\nFirst execve failed\n");
}

void	second_child(int pipefd[2], t_cmd *cmd, char **envp)
{
	if (pipefd[1])
		close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error\n", cmd, pipefd);
	if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error\n", cmd, pipefd);
	if (pipefd[0])
		close(pipefd[0]);
	if (cmd->infile != -1 && cmd->infile)
		close(cmd->infile);
	if (cmd->outfile != -1 && cmd->outfile)
		close(cmd->outfile);
	execve(cmd->good_path2, cmd->cmd2, envp);
	ultimate_free(cmd, pipefd);
	perror("Error\nSecond execve failed\n");
	exit(EXIT_FAILURE);
}
