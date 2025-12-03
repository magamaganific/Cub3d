/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:06:54 by frlorenz          #+#    #+#             */
/*   Updated: 2025/11/27 19:21:57 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_memo(char **stash)
{
	free (*stash);
	*stash = NULL;
}

char	*read_line(int fd, char *stash)
{
	int		data;
	char	*buffer;

	data = 1;
	buffer = (char *) ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (clean_memo(&stash), NULL);
	if (!stash)
		stash = (char *) ft_calloc_gnl(1, sizeof(char));
	if (!stash)
		return (clean_memo(&buffer), NULL);
	while (data > 0)
	{
		data = read(fd, buffer, BUFFER_SIZE);
		if (data < 0)
			return (clean_memo(&buffer), clean_memo(&stash), NULL);
		if (data == 0)
			return (clean_memo(&buffer), stash);
		stash = ft_strjoin_gnl(stash, buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
		buffer = ft_memset_gnl(buffer, 0, BUFFER_SIZE);
	}
	return (clean_memo(&buffer), stash);
}

char	*write_line(char *stash)
{
	char	*line;
	int		memory;

	if (stash[0] == '\0')
		return (NULL);
	memory = 0;
	while (stash[memory] != '\n' && stash[memory] != '\0')
		memory++;
	if (stash[memory] == '\n')
		line = (char *) ft_calloc_gnl(memory + 2, sizeof(char));
	else
		line = (char *) ft_calloc_gnl(memory + 1, sizeof(char));
	if (!line)
		return (clean_memo(&stash), NULL);
	while (memory >= 0)
	{
		line[memory] = stash[memory];
		memory--;
	}
	return (line);
}

char	*clean_stash(char *stash)
{
	char	*temp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	len = ft_strlen_gnl(stash) - i;
	temp = (char *) ft_calloc_gnl(len, sizeof(char));
	if (!temp)
		return (clean_memo(&stash), NULL);
	while (len-- > 0)
		temp[j++] = stash[++i];
	return (clean_memo(&stash), temp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = write_line(stash);
	stash = clean_stash(stash);
	return (line);
}
