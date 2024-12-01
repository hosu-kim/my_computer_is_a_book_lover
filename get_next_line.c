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
 * @param fd The file descriptor to read from
 * @param str The string to append the read data to.
 * @return The updated string with the read data appended, or NULL on failure.
*/
char	*line_into_storage(int fd, char *line_storage)
{
	char	*line;
	int		bytes_read;
	char	*temp;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	if (!line_storage)
		line_storage = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		ft_bzero(line, BUFFER_SIZE + 1);
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			free(line_storage);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		temp = ft_strjoin(line_storage, line);
		free(line_storage);
		line_storage = temp;
		if (ft_strchr(line_storage, '\n'))
			break ;
	}
	free(line);
	return (line_storage);
}
/**
* 27: malloc((BUFFER_SIZE + 1) * sizeof(char)): line 버퍼 할당 시 널 종료 문자를 위한 공간 확보
* 36: read (파일 디스크립터, 저장할 버퍼, 몇 바이트)
*		반환: 읽어온 바이트 수, 오류 시 -1,
*		세 번째 매개변수와 동일할 것 같지만, 불러온 데이터가 '적거나 없으면' 값이 달라질 수 있음.
* 41: return (NULL): Error indication
*/

// @brief Main fuction;  
char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffered_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffered_str = line_into_storage(fd, buffered_str);
	if (!buffered_str)
		return (NULL);
	line = extract_line(buffered_str);
	buffered_str = new_left_str(buffered_str);
	return (line);
}
/**
* static 변수는 한 번만 초기화됨; 기본 초기화값: NULL
*/

/**
 * @brief Extracts a line in left_str and appends it into line.
 * @param line_storage
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

char	*new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	new_str = malloc((ft_strlen(left_str) - i + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		new_str[j++] = left_str[i++];
	new_str[j] = '\0';
	free(left_str);
	return (new_str);
}
