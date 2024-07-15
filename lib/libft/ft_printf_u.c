/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:35:29 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 16:56:41 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(unsigned int i)
{
	int	digits;

	digits = 0;
	if (i == 0)
		return (1);
	while (i > 0)
	{
		i = i / 10;
		digits++;
	}
	return (digits);
}

static void	extract_nbr(char *out, unsigned int i, int length)
{
	out[length--] = '\0';
	if (i == 0)
		out[length] = 48;
	while (i > 0)
	{
		out[length--] = (i % 10) + 48;
		i = i / 10;
	}
}

char	*ft_printf_u(unsigned int i)
{
	char	*out;
	int		length;

	length = count_digits(i);
	out = malloc((length + 1) * sizeof(char));
	if (!out)
		return (0);
	extract_nbr(out, i, length);
	return (out);
}
