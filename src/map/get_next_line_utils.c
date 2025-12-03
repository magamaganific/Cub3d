/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:07:16 by frlorenz          #+#    #+#             */
/*   Updated: 2025/11/27 19:22:13 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_memset_gnl(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		s[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

void	*ft_calloc_gnl(size_t count, size_t len)
{
	void	*m;
	size_t	n;

	n = count * len;
	if (n == 0)
		return (NULL);
	m = malloc(n);
	if (!m)
		return (NULL);
	m = ft_memset_gnl(m, 0, n);
	return (m);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if ((char) c == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		size;
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	str = (char *) ft_calloc_gnl(size + 1, sizeof(char));
	if (!str)
		return (clean_memo(&s1), NULL);
	i = 0;
	while (i < size && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < size && s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (clean_memo(&s1), str);
}
