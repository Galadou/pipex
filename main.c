#include "header.h"
#include "stdio.h"

char	**catch(char **envp)
{
	int		y;
	int		i;
	char	**path;

	y = 0;
	if (!envp)
	{
		ft_putstr_fd("Error pipex : Envp is empty\n", 2);
		exit (1);
	}
	i = 0;
	while(envp[y] != NULL)
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

int	main(int argc, char **argv, char *envp[])
{
	int		infile;
	int		outfile;
	char	**path;
	int	i;

	i = 0;
	path = catch(envp);
	while (path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
	check(argc, path);
	free (path);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY);
	return (0);
}
