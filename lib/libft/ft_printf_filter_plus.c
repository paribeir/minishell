/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_filter_plus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:08:11 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 17:03:35 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_filter_plus(char *out)
{
	char	*new_string;

	new_string = malloc(((int)ft_strlen(out) + 2) * sizeof(char));
	if (!new_string)
		return (NULL);
	new_string[0] = '+';
	ft_strlcpy(&new_string[1], out, ((int)ft_strlen(out) + 1));
	free(out);
	return (new_string);
}
