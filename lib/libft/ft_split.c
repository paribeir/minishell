/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:05:34 by jdach             #+#    #+#             */
/*   Updated: 2023/11/22 16:00:45 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_words(char const *s, char c)
{
	int	count;
	int	started;

	count = 0;
	started = -1;
	while (*s != '\0')
	{
		if (started == -1 && *s != c)
		{
			started = 1;
			count++;
		}
		else if (started == 1 && *s == c)
			started = -1;
		s++;
	}
	return (count);
}

static	void	extract_strings(char **mother, char const *s, char c)
{
	int	start;
	int	child;
	int	i;

	start = -1;
	child = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (start == -1 && s[i] != c)
			start = i;
		else if (start != -1 && (s[i] == c))
		{
			mother[child++] = ft_substr(s, start, (i - start));
			start = -1;
		}
		i++;
	}
	if (s[i] == '\0' && start != -1)
		mother[child] = ft_substr(s, start, (i - start + 1));
}

char	**ft_split(char const *s, char c)
{
	char	**mother;
	int		words;

	words = count_words(s, c) + 1;
	mother = (char **)malloc(words * sizeof(char *));
	if (!mother || !s)
		return (0);
	extract_strings(mother, s, c);
	mother[words - 1] = 0;
	return (mother);
}
