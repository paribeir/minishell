/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_filter_space.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:03:22 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 17:03:39 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_filter_space(char *out)
{
	char	*new_string;

	new_string = malloc(((int)ft_strlen(out) + 2) * sizeof(char));
	if (!new_string)
		return (NULL);
	new_string[0] = ' ';
	ft_strlcpy(&new_string[1], out, ((int)ft_strlen(out) + 1));
	free(out);
	return (new_string);
}
