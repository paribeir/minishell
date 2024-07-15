/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:52 by jdach             #+#    #+#             */
/*   Updated: 2023/11/22 16:00:52 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_ptr;
	const unsigned char	*s2_ptr;

	s1_ptr = (const unsigned char *)s1;
	s2_ptr = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*s1_ptr == *s2_ptr)
	{
		if (n == 1)
			break ;
		s1_ptr++;
		s2_ptr++;
		n--;
	}
	return ((unsigned char)*s1_ptr - (unsigned char)*s2_ptr);
}
