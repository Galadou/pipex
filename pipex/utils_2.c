/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:07:11 by gmersch           #+#    #+#             */
/*   Updated: 2024/04/05 11:19:23 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		f;
	char	*str;

	f = 0;
	i = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1)+1);
	i = ft_strlen(s1);
	str[i] = s2[f];
	while ((unsigned long int)i < ft_strlen(s1) + ft_strlen(s2))
	{
		str[i] = s2[f];
		f++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*pt_s1;
	const unsigned char	*pt_s2;

	pt_s1 = (const unsigned char *)s1;
	pt_s2 = (const unsigned char *)s2;
	if (ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
	{
		if (n == 0)
			return (0);
		else
			return (*pt_s1 - *pt_s2);
	}
	if (*pt_s1 == '\0' || *pt_s2 == '\0')
		return (*pt_s1 - *pt_s2);
	while (n > 0 && *pt_s1 != '\0')
	{
		if (*pt_s1 != *pt_s2)
			return (*pt_s1 - *pt_s2);
		pt_s1++;
		pt_s2++;
		n--;
	}
	if (*pt_s1 != *pt_s2 && n > 0)
		return (*pt_s1 - *pt_s2);
	return (0);
}

int	charchr(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '/')
			return (1);
		x++;
	}
	return (0);
}

void	init_struct(t_cmd *cmd)
{
	cmd->cmd1 = NULL;
	cmd->cmd2 = NULL;
	cmd->good_path2 = NULL;
	cmd->good_path = NULL;
	cmd->file1_error = 0;
	cmd->gp_not_malloc = 0;
	cmd->gp2_not_malloc = 0;
}
