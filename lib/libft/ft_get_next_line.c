/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:47:35 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 15:51:24 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clean_ptr(char **ptr)
{
	if (*ptr != NULL)
		free (*ptr);
	*ptr = NULL;
}

static char	*extract_string(char *s, char **output)
{
	char	*s2;

	if (s[0] == '\0')
		return (*output = NULL, clean_ptr(&s), NULL);
	if (!ft_strchr(s, '\n'))
		return (*output = s, NULL);
	*output = ft_substr(s, 0, ft_strchr(s, '\n') - &s[0] + 1);
	s2 = ft_substr(s, ft_strchr(s, '\n') - &s[0] + 1, ft_strlen(s));
	return (clean_ptr(&s), s2);
}

static char	*fill_string(int fd, char *string)
{
	char		*buffer;
	char		*temp_ptr;
	ssize_t		bytes_read;

	if (!string)
		string = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (string && !ft_strchr(string, '\n'))
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_ptr(&buffer), clean_ptr(&string), NULL);
		if (bytes_read == 0)
			return (clean_ptr(&buffer), string);
		buffer[BUFFER_SIZE] = '\0';
		temp_ptr = string;
		string = ft_strjoin(string, buffer);
		clean_ptr(&temp_ptr);
		clean_ptr(&buffer);
	}
	return (string);
}

char	*ft_get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*string;
	char		*output;

	output = NULL;
	string = NULL;
	if (fd > FOPEN_MAX)
		return (NULL);
	else if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (clean_ptr(&stash[fd]), NULL);
	else if (stash[fd] && ft_strchr(stash[fd], '\n'))
		return (stash[fd] = extract_string(stash[fd], &output), output);
	else if (stash[fd])
		string = fill_string(fd, stash[fd]);
	else
		string = fill_string(fd, string);
	if (!string)
		return (clean_ptr(&output), NULL);
	stash[fd] = extract_string(string, &output);
	return (output);
}
