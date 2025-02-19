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

/**
 * @brief Reads from file decriptor and sotres content in line storage
 * 
 * @param fd The file descriptor to read form
 * @param line_storage The buffer where the read content is stored
 * @return char* Returns the updated line_storage containing the read content
 *         Returns NULL if reading fails
 * 
 * @details This function reads BUFFER_SIZE bytes at a time from the file desciptor
 *          and appends the content to line_storage untill a newline is found or
 *          EOF is reached.
 */
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

/**
 * @brief Extracts a single line from the line storage
 * 
 * @param line_storage The buffeer containing all read content
 * @return char* Returns a newly allocated string containing the extracted line
 *         (including newline if present)
 *         Returns NULL if line_storage is empty or allocation fails.
 * 
 * @details Extracts characters from line_storage until a newline or null terminator
 *          is encountered. The extracted line includes the newline chracter if present.
 */
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

/**
 * @brief Creates a new line storage without the extracted line
 * 
 * @param line_storage the current line storage buffer
 * @return char* Returns a newly allocated string containing the remaining content
 *         Returns NULL if no content remains or allocation fails
 * 
 * @details After a line has been extracted, this fundtion creates a new storage
 *          containing only the remaining content after the extracted line.
 *          The original line_storage is freed.
 * 
 */
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
 * @brief Reads and returns one line at a time from a file descriptor
 * 
 * @param fd The file descriptor to read from
 * @return char* Returns a newly allocated string containing the next line
 *         Returns NULL if reading fails, fd is invalid, or BUFFER_SIZE is invalid
 * 
 * @details This function implements a line reading mechanism that:
 *          1. Reads from fd and stores content in a static buffer (line_storage)
 *          2. Extracts one complete line form the stored content
 *          3. Updates the storage to remove the extracted line
 *          4. Returns the extracted line
 *
 *          The static line_sotrage maintains state between function calls,
 *          allowing for efficient reading of files line by line.
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
