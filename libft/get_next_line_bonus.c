/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 07:39:10 by ashalagi          #+#    #+#             */
/*   Updated: 2023/07/19 14:00:29 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_line(char *buf, char **line)
{
	int		i;
	int		j;
	int		flag_line;
	char	*find_line;

	i = 0;
	j = -1;
	while (buf[i] && buf[i] != '\n')
		i++;
	flag_line = 0;
	if (buf[i] == '\n')
		flag_line = 1;
	find_line = malloc(i + flag_line + 1);
	if (find_line == NULL)
		return (-1);
	while (++j < i + flag_line)
		find_line[j] = buf[j];
	find_line[j] = '\0';
	*line = ft_strjoin_gnl(*line, find_line);
	if (*line == NULL)
		return (-1);
	copy_string_contents(buf, &buf[i + flag_line]);
	free (find_line);
	return (flag_line);
}

char	*free_line(char **line)
{
	if (*line != NULL)
		free(*line);
	return (NULL);
}

char	*ft_count(int fd, char *buf, char *line)
{
	int	flag_line;
	int	count_byte;

	flag_line = 0;
	while (flag_line == 0)
	{
		flag_line = find_line(buf, &line);
		if (flag_line == -1)
			return (free_line(&line));
		if (flag_line == 0)
		{
			count_byte = read(fd, buf, BUFFER_SIZE);
			if (count_byte == 0 && *line)
				flag_line = 1;
			else if (count_byte <= 0)
				return (free_line(&line));
			buf[count_byte] = '\0';
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buf[1024][BUFFER_SIZE + 1];
	char			*line;

	if (!ft_strlen_gnl(buf[fd]))
		buf[fd][0] = '\0';
	line = init_string();
	if (!line)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(line);
		return (NULL);
	}
	return (ft_count(fd, buf[fd], line));
}
/*
int	main()
{
	int	fd;
	int	i;

	fd = open("text.txt", O_RDONLY);
	i = 0;
	while (i < 11)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close(fd);
}
*/
