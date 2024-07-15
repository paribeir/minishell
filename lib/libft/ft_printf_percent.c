/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:53:24 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 16:56:34 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_percent(void)
{
	char	*out;

	out = malloc(2 * sizeof(char));
	if (!out)
		return (NULL);
	out[0] = '%';
	out[1] = '\0';
	return (out);
}
