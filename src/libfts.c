/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:08:42 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/16 13:08:44 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

size_t	ft_strlen(const char *c)
{
	size_t	n;

	n = 0;
	while (c[n])
		n++;
	return (n);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dst;
	size_t			p;

	p = 0;
	dst = (unsigned char *) s;
	while (p < n)
	{
		dst[p] = '\0';
		p++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;

	memory = malloc (size * nmemb);
	if (!memory)
		return (NULL);
	ft_bzero(memory, size * nmemb);
	return (memory);
}

int	ft_atoi(const char *nptr)
{
	int	sgn;
	int	dig;
	int	num;

	sgn = 1;
	dig = 0;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sgn = -sgn;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		dig = *nptr - '0';
		num = num * 10 + dig;
		nptr++;
	}
	num = num * sgn;
	return (num);
}
