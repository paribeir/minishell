/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:36:07 by jdach             #+#    #+#             */
/*   Updated: 2023/11/22 16:00:18 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (s1[start] != '\0' && ft_strchr((char *)set, s1[start]) != 0)
		start++;
	end = ft_strlen(s1) - 1;
	while (end > 0 && ft_strchr((char *)set, s1[end]) != 0)
		end--;
	if (start > end)
		len = 0;
	else
		len = end - start + 1;
	return (ft_substr(s1, start, len));
}
