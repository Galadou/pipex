/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:02:35 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/16 19:52:05 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int pipefd[2], t_cmd *cmd, char **envp)
{
	if (dup2(cmd->infile, STDIN_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error\n", cmd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error\n", cmd);
	if (pipefd[0])
		close(pipefd[0]);
	if (pipefd[1])
		close(pipefd[1]);
	if (cmd->infile != -1 && cmd->infile)
		close(cmd->infile);
	if (cmd->outfile != -1 && cmd->outfile)
		close(cmd->outfile);
	execve(cmd->good_path, cmd->cmd1, envp);
	ultimate_free(cmd);
	perror("Error\nFirst execve failed\n");
}

void	second_child(int pipefd[2], t_cmd *cmd, char **envp)
{
	if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		error_free_and_exit("Error\nFonction dup2 error\n", cmd);
	if (pipefd[0])
		close(pipefd[0]);
	if (pipefd[1])
		close(pipefd[1]);
	if (cmd->infile != -1 && cmd->infile)
		close(cmd->infile);
	if (cmd->outfile != -1 && cmd->outfile)
		close(cmd->outfile);
	execve(cmd->good_path2, cmd->cmd2, envp);
	ultimate_free(cmd);
	perror("Error\nSecond execve failed\n");
}
