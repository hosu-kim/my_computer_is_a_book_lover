/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:24:25 by hoskim            #+#    #+#             */
/*   Updated: 2024/10/25 23:24:25 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Takes a line from the text file and append it into line_storage
char	*line_into_storage(int fd, char *line_storage)
{
	char	*line;
	int		bytes_read;

	line = malloc(BUFFER_SIZE + 1);
	if (!line_storage)
		line_storage = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			free(line_storage);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		line[bytes_read] = '\0';
		line_storage = ft_strjoin_and_free(line_storage, line);
		if (ft_strchr(line_storage, '\n'))
			break ;
	}
	free(line);
	return (line_storage);
}

// Extracts a line from line_storage and appends it into extracted_line.
char	*extract_line(char *line_storage)
{
	int		i;
	char	*extracted_line;

	i = 0;
	if (!line_storage[i])
		return (NULL);
	while (line_storage[i] && line_storage[i] != '\n')
		i++;
	extracted_line = malloc((i + 2) * sizeof(char));
	if (!extracted_line)
		return (NULL);
	i = 0;
	while (line_storage[i] && line_storage[i] != '\n')
	{
		extracted_line[i] = line_storage[i];
		i++;
	}
	if (line_storage[i] == '\n')
	{
		extracted_line[i] = line_storage[i];
		i++;
	}
	extracted_line[i] = '\0';
	return (extracted_line);
}

// After printing a line, removes it in line_storage
char	*new_line_storage(char *line_storage)
{
	int		i;
	int		j;
	char	*new_storage;

	i = 0;
	while (line_storage[i] && line_storage[i] != '\n')
		i++;
	if (!line_storage[i])
	{
		free(line_storage);
		return (NULL);
	}
	new_storage = malloc((ft_strlen(line_storage) - i + 1) * sizeof(char));
	if (!new_storage)
		return (NULL);
	i++;
	j = 0;
	while (line_storage[i])
		new_storage[j++] = line_storage[i++];
	new_storage[j] = '\0';
	free(line_storage);
	return (new_storage);
}

/**
 * @brief main function; 
 * 		1. stores lines from fd into line_storage.
 * 		2. extracts one line and assigns it to line.
 * 		3. removes it in line_storage.
 * @param fd from open()
 */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line_storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_storage = line_into_storage(fd, line_storage);
	if (!line_storage)
		return (NULL);
	line = extract_line(line_storage);
	line_storage = new_line_storage(line_storage);
	return (line);
}
