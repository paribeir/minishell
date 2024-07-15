/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:00:44 by joda              #+#    #+#             */
/*   Updated: 2023/11/22 15:58:01 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_digits(long n)
{
	int	digit_count;

	digit_count = 0;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n = n / 10;
		digit_count++;
	}
	digit_count++;
	return (digit_count);
}

static	void	split_number(long long_n, int digits, char *a)
{
	while (long_n >= 10)
	{
		a[digits--] = (long_n % 10) + 48;
		long_n = long_n / 10;
	}
	a[digits] = long_n + 48;
}

char	*ft_itoa(int n)
{
	long	long_n;
	char	*a;
	int		digits;

	long_n = (long)n;
	digits = count_digits(long_n);
	if (long_n < 0)
	{
		a = (char *)malloc(digits + 2 * sizeof(char));
		if (!a)
			return (NULL);
		a[0] = '-';
		long_n = -long_n;
		a[digits + 1] = '\0';
	}
	else
	{
		a = (char *)malloc(digits + 1 * sizeof(char));
		if (!a)
			return (NULL);
		a[digits--] = '\0';
	}
	split_number(long_n, digits, a);
	return (a);
}
