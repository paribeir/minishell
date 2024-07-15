/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:29:36 by joda              #+#    #+#             */
/*   Updated: 2024/01/20 16:56:37 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_null_string(void)
{
	char	*empty_string;
	char	*out;

	empty_string = "";
	out = malloc(1 * sizeof(char));
	if (!out)
		return (NULL);
	ft_strlcpy(out, empty_string, (1));
	return (out);
}

char	*ft_printf_s(char *str, t_flags *flags)
{
	size_t	length;
	char	*null_str;
	char	*out;

	null_str = "(null)";
	if (str == NULL && flags->dot > 0 && flags->dot < 6)
		return (return_null_string());
	if (str == NULL)
	{
		length = ft_strlen(null_str);
		out = malloc(length + 1 * sizeof(char));
		if (!out)
			return (NULL);
		ft_strlcpy(out, null_str, (length + 1));
	}
	else
	{
		length = ft_strlen(str);
		out = malloc(length + 1 * sizeof(char));
		if (!out)
			return (NULL);
		ft_strlcpy(out, str, (length + 1));
	}
	return (out);
}
