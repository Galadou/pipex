/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:45:48 by gmersch           #+#    #+#             */
/*   Updated: 2024/03/15 16:11:06 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == 0)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_strdup(const char *s)
{
	char	*str;

	if (s == 0)
		while (s)
			s++;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s, (ft_strlen(s) +1));
	return (str);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		i = ft_strlen(src);
		return (i);
	}
	while (size - 1 > i && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	i = ft_strlen(src);
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*str;

	i = 0;
	if (!s)
		return (0);
	if ((start > (unsigned int)ft_strlen(s)))
		return (ft_strdup(""));
	j = ft_strlen(&s[start]);
	if (j < len)
		len = j;
	str = malloc((len +1) * sizeof(char));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
