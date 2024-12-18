/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:48:49 by rafael            #+#    #+#             */
/*   Updated: 2024/12/11 10:48:49 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*text_to_stash(int fd, char *buf, char *stash)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line > 0)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!stash)
			stash = ft_strdup("");
		if (!stash)
			return (NULL);
		temp = stash;
		stash = ft_strjoin(temp, buf);
		free(temp);
		if (!stash)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (stash);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*stash;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	stash = ft_substr(line, count + 1, ft_strlen(line) - count - 1);
	if (!stash)
		return (NULL);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line[count + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = text_to_stash(fd, buf, stash[fd]);
	free(buf);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = extract(line);
	return (line);
}
