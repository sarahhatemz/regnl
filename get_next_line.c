/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:04:40 by salzghou          #+#    #+#             */
/*   Updated: 2025/10/26 00:10:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update(char **store)
{
	char	*new;

	if (!store || !*store)
		return (NULL);
	new = ft_strchr(*store, '\n');
	if (!new)
	{
		free(*store);
		*store = NULL;
		return (NULL);
	}
	new = ft_strdup(new + 1);
	free(*store);
	if (!new || new[0] == '\0')
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static char	*linef(char **store)
{
	int		i;
	char	*line;

	i = 0;
	if (!store || !*store)
		return (NULL);
	while ((*store)[i] && (*store)[i] != '\n')
		i++;
	line =NULL;// malloc(i + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, *store, i);
	if ((*store)[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	join_free(char **store, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(*store, buff);
	free(*store);
	if (!tmp)
	{
		*store = NULL;
		return (1);
	}
	*store = tmp;
	return (0);
}

static int	readjoin(int fd, char **store)
{
	char	*buff;
	int		n;

	n = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (1);
	while (!ft_strchr(*store, '\n') && n > 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n < 0)
		{
			free(buff);
			return (1);
		}
		if (n == 0)
			break ;
		buff[n] = '\0';
		if (join_free(store, buff))
		{
			free(buff);
			return (1);
		}
	}
	free(buff);
	if (!*store || (*store && (*store)[0] == '\0'))
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!store)
		store = ft_strdup("");
	if (!store || readjoin(fd, &store))
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	line = linef(&store);
	if (!line)
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	store = update(&store);
	return (line);
}

int	main(void){
	int fd = open("txt.txt", O_RDONLY);
	char *line = NULL;
	while ((line = get_next_line(fd)) != NULL){
	printf("%s", line);
	free(line);
    }
close(fd);
}
