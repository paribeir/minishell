/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_filter_x.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:12:34 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 17:03:51 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_filter_x(char *out, char c)
{
	char	*new_string;

	new_string = malloc(((int)ft_strlen(out) + 3) * sizeof(char));
	if (!new_string)
		return (NULL);
	new_string[0] = '0';
	new_string[1] = c;
	ft_strlcpy(&new_string[2], out, ((int)ft_strlen(out) + 1));
	free(out);
	return (new_string);
}
