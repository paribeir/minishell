/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_filter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:58:58 by joda              #+#    #+#             */
/*   Updated: 2024/01/20 17:01:49 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_filter(t_flags *flags, char c, char *out)
{
	if ((c == 'i' || c == 'd') && flags->plus > 0 && out[0] != '-')
		out = (ft_printf_filter_plus(out));
	if (((c == 'x' || c == 'X') && flags->hash > 0 && out[0] != '0'))
		out = (ft_printf_filter_x(out, c));
	if ((c == 'd' || c == 'i' || c == 's' || c == 'u' || c == 'x' || c == 'X') \
	&& flags->dot > -1)
		out = (ft_printf_filter_dot(flags, out, c));
	if ((c == 'i' || c == 'd') && flags->space && *out != '+' && *out != '-')
		out = (ft_printf_filter_space(out));
	if ((flags->width > 0 && flags->width > (int)ft_strlen(out)))
		out = (ft_printf_filter_width(flags, out, c));
	return (out);
}
