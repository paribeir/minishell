/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:37:21 by joda              #+#    #+#             */
/*   Updated: 2024/01/20 16:56:32 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countbase16(unsigned long int i)
{
	int		length;

	length = 0;
	while (i >= 16)
	{
		i = i / 16;
		length++;
	}
	length++;
	return (length);
}

static void	getbase16(unsigned long int i, int length, char *out)
{
	char	*str_b16;

	str_b16 = "0123456789abcdef";
	out[0] = '0';
	out[1] = 'x';
	length--;
	out[length--] = '\0';
	while (i > 0)
	{
		out[length--] = str_b16[i % 16];
		i = i / 16;
	}
}

char	*ft_printf_p(void *p)
{
	unsigned long int	i;
	char				*out;
	char				*nullstring;
	int					length;

	i = (unsigned long int)p;
	nullstring = "(nil)";
	if (i == 0)
	{
		out = malloc(6 * sizeof(char));
		if (!out)
			return (NULL);
		ft_strlcpy(out, nullstring, ft_strlen(nullstring) + 1);
		return (out);
	}
	length = countbase16(i) + 3;
	out = malloc(length * sizeof(char));
	if (!out)
		return (NULL);
	getbase16(i, length, out);
	return (out);
}
