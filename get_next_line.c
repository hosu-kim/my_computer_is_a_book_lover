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
 * @brief Reads a line from a file descriptor and appends it to a string.
 * @param fd fd to read from
 * @param line_storage string to append the data into.
 * @return line_storage / NULL on failure.
*/
char	*line_into_storage(int fd, char *line_storage)
{
	char	*line;
	char	*temp;
	int		bytes_read;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	if (!line_storage)
		line_storage = ft_strdup("");
	bytes_read = read(fd, line, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		line[bytes_read] = '\0';
		temp = ft_strjoin(line_storage, line);
		free(line_storage);
		line_storage = temp;
		if (ft_strchr(line_storage, '\n'))
			break ;
		bytes_read = read(fd, line, BUFFER_SIZE);
	}
	free(line);
	return (line_storage);
}
/*
malloc((BUFFER_SIZE + 1) * sizeof(char)): line 버퍼 할당 시 널 종료 문자를 위한 공간 확보
read (파일 디스크립터, 저장할 버퍼, 몇 바이트?)
	-반환: 읽어온 바이트 수, 오류 시 -1,
	-불러온 데이터가 '적거나 없으면' 세번째 매개변수와 값이 달라질 수 있음.
return (NULL): Error indication
*/

/*
Extracts a line in left_str and appends it into line.
*/
char	*extract_line(char *line_storage)
{
	int		i;
	char	*extract;

	i = 0;
	if (!line_storage[i])
		return (NULL);
	while (line_storage[i] && line_storage[i] != '\n')
		i++;
	extract = malloc((i + 2) * sizeof(char));
	if (!extract)
		return (NULL);
	i = 0;
	while (line_storage[i] && line_storage[i] != '\n')
	{
		extract[i] = line_storage[i];
		i++;
	}
	if (line_storage[i] == '\n')
	{
		extract[i] = line_storage[i];
		i++;
	}
	extract[i] = '\0';
	return (extract);
}

/**
 * @brief After printing a line, removes it in line_storage
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
/*
* static 변수는 한 번만 초기화됨; 기본 초기화값: NULL
*/
