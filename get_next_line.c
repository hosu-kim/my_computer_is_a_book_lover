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

// reads a line and saves it into str
char	*one_line_into_str(int fd, char *str)
{
	char	*line;
	int		bytes_read;
	char	*temp;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		ft_bzero(line, BUFFER_SIZE + 1);
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			free(str);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		temp = ft_strjoin(str, line);
		free(str);
		str = temp;
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(line);
	return (str);
}
/*
21: malloc((BUFFER_SIZE + 1) * sizeof(char)): line 버퍼 할당 시 널 종료 문자를 위한 공간 확보
27: read (파일 디스크립터, 저장할 버퍼, 몇 바이트)
		반환: 읽어온 바이트 수, 오류 시 -1, 
		세 번째 매개변수와 동일할 것 같지만, 불러온 데이터가 '적거나 없으면' 값이 달라질 수 있음.
31: return (NULL): Error indication
*/

// main function
char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffered_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffered_str = one_line_into_str(fd, buffered_str);
	if (!buffered_str)
		return (NULL);
	line = extract_line(buffered_str);
	buffered_str = new_left_str(buffered_str);
	return (line);
}
/*
static 변수는 한 번만 초기화됨; 기본 초기화값: NULL
*/
/*
67: line = malloc((i + 2) * sizeof(char));
	(i + 2): 널 문자와 줄바꿈 문자 포함
*/

char	*extract_line(char *left_str)
// extracts a line in left_str and saves it into line(return).
{
	int		i;
	char	*line;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		line[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		line[i] = left_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
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
