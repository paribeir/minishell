/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getflags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:39:26 by joda              #+#    #+#             */
/*   Updated: 2024/01/20 16:56:27 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reset_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->dot = -1;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->width = 0;
	flags->specialc = 0;
}

static const char	*getflag_width(const char *s, t_flags *flags)
{
	flags->width = ft_atoi(s);
	while (*s >= '0' && *s <= '9' && *(s + 1) >= '0' && *(s + 1) <= '9')
		s++;
	return (s);
}

static const char	*getflag_dot(const char *s, t_flags *flags)
{
	s++;
	if (*s < '0' || *s > '9')
	{
		flags->dot = 0;
		return (--s);
	}
	flags->dot = ft_atoi(s);
	while (*s >= '0' && *s <= '9' && *(s + 1) >= '0' && *(s + 1) <= '9')
		s++;
	return (s);
}

const char	*ft_printf_getflags(const char *s, t_flags *flags)
{
	reset_flags(flags);
	while (*s != 'c' && *s != 'i' && *s != 'd' && *s != 's' && *s != 'p' \
	&& *s != 'u' && *s != 'x' && *s != 'X' && *s != '\0' && *s != '%')
	{
		if (*s == '-')
			flags->minus = 1;
		else if (*s == '0')
			flags->zero = 1;
		else if (*s == '#')
			flags->hash = 1;
		else if (*s == ' ')
			flags->space = 1;
		else if (*s == '+')
			flags->plus = 1;
		else if (*s >= '0' && *s <= '9')
			s = getflag_width(s, flags);
		else if (*s == '.')
			s = getflag_dot(s, flags);
		s++;
	}
	return (s);
}
