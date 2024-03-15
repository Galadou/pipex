#include "header.h"

void	check(int argc, char **path)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error\nNot good number of arg", 2);
		exit (0);
	}
	if (!path)
	{
		ft_putstr_fd("Error\nPath not valid", 2);
		exit (0);
	}
}
