/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:37:21 by joda              #+#    #+#             */
/*   Updated: 2024/01/20 16:56:43 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countbase16(unsigned int i)
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

static void	getbase16(unsigned long int i, int length, char *out, char c)
{
	char	*str_b16;
	char	*str_b16_c;

	str_b16 = "0123456789abcdef";
	str_b16_c = "0123456789ABCDEF";
	out[length--] = '\0';
	if (i == 0)
		out[length] = 48;
	while (i > 0)
	{
		if (c == 'x')
			out[length--] = str_b16[i % 16];
		else if (c == 'X')
			out[length--] = str_b16_c[i % 16];
		i = i / 16;
	}
}

char	*ft_printf_x(unsigned int i, char c)
{
	char	*out;
	int		length;

	length = countbase16(i);
	out = malloc((length + 1) * sizeof(char));
	if (!out)
		return (NULL);
	getbase16(i, length, out, c);
	return (out);
}
