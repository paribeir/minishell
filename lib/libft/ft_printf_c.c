/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:28:25 by joda              #+#    #+#             */
/*   Updated: 2024/01/20 16:57:55 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_c(int i, t_flags *flags)
{
	char	c;
	char	*out;

	c = (char)i;
	if (c == 0)
		flags->specialc = 1;
	out = malloc(2 * sizeof(char));
	if (!out)
		return (NULL);
	out[0] = c;
	out[1] = '\0';
	return (out);
}
