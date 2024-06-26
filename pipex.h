/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:06:55 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/20 16:13:05 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_cmd_and_files
{
	int		infile;
	int		outfile;

	char	*good_path;
	char	*good_path2;
	char	**cmd1;
	char	**cmd2;

	char	**path;
	int		cmd1_error;
	int		cmd2_error;

	int		file1_error;
	int		file2_error;
	int		gp_not_malloc;
	int		gp2_not_malloc;

}t_cmd;

struct s_Variable
{
	int	i;
	int	f;
	int	lastf;
};

void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		charchr(char *str);

void	verif_arg_and_path(int argc, char **path, t_cmd *cmd);
int		is_only_slash(char *str, int c, t_cmd *cmd);
void	path_creator(t_cmd *cmd);
char	*path_1_creator(t_cmd *cmd);
char	*path_2_creator(t_cmd *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	family_process(char **envp, t_cmd *cmd);
void	process_parent(int pipefd[2], t_cmd *cmd, char **envp);
void	first_child(int pipefd[2], t_cmd *cmd, char **envp);
void	second_child(int pipefd[2], t_cmd *cmd, char **envp);

void	error_free_and_exit(char *error, t_cmd *cmd, int pipefd[2]);
void	init_struct(t_cmd *cmd);

void	free_tab(char **tab);
void	ultimate_free(t_cmd *cmd, int pipefd[2]);

#endif
