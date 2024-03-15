# ifndef HEADER_H
# define HEADER_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}	t_list;

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

void	check(int argc, char **path);

# endif
