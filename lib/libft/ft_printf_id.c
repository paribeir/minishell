/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:36:10 by joda              #+#    #+#             */
/*   Updated: 2024/01/20 16:56:29 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int i)
{
	int	val;

	val = 0;
	if (i == -2147483648)
		val = 11;
	else if (i < 0)
	{
		i = -i;
		val += 1;
	}
	else if (i == 0)
		val = 1;
	while (i > 0)
	{
		i = i / 10;
		val += 1;
	}
	return (val);
}

static void	extract_nbr(char *out, int i, int length)
{
	char	*min_int;

	min_int = "-2147483648";
	if (i == -2147483648)
		ft_strlcpy(out, min_int, length + 1);
	else if (i < 0)
	{
		out[0] = '-';
		i = -i;
	}
	out[length--] = '\0';
	if (i == 0)
		out[length] = 48;
	while (i > 0)
	{
		out[length--] = (i % 10) + 48;
		i = i / 10;
	}
}

char	*ft_printf_id(int i)
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
