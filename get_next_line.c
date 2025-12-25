/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:05:51 by isoulima          #+#    #+#             */
/*   Updated: 2025/12/25 17:12:45 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*error_free(char *buf, char *stash)
{
	free(stash);
	free(buf);
	return (NULL);
}

static char	*stash_join(char *stash, char *buf)
{
	char	*tmp;

	tmp = stash;
	stash = ft_strjoin(stash, buf);
	free(tmp);
	return (stash);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	int		read_ret;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(stash);
		return (NULL);
	}
	read_ret = 1;
	while (ft_strchr(stash, '\n') == NULL && read_ret != 0)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret == -1)
			return (error_free(buf, stash));
		if (read_ret == 0)
			break ;
		buf[read_ret] = '\0';
		stash = stash_join(stash, buf);
		if (stash == NULL)
			return (error_free(buf, NULL));
	}
	free(buf);
	return (stash);
}

static char	*stash_line(char **stash)
{
	char	*line;
	char	*tmp;
	char	*nl;

	if (*stash == NULL || **stash == '\0')
		return (NULL);
	nl = ft_strchr(*stash, '\n');
	if (nl != NULL)
	{
		line = ft_substr(*stash, 0, nl - *stash + 1);
		tmp = ft_strdup(nl + 1);
		free(*stash);
		*stash = tmp;
		if (line == NULL || *stash == NULL)
			return (NULL);
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = ft_strdup("");
		if (stash == NULL)
			return (NULL);
	}
	stash = read_to_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = stash_line(&stash);
	return (line);
}
