/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:41:16 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 17:04:08 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	specialc(t_flags *flags, int i, int *val)
{
	int	printed;

	printed = 0;
	if (flags->specialc && i == 1 && flags->minus == 1)
	{
		printed += write(1, "\0", 1);
		*val = *val + 1;
	}
	if (flags->specialc && i == 2 && flags->minus != 1)
	{
		printed += write(1, "\0", 1);
		*val = *val + 1;
	}
	return (printed);
}

static int	printall(t_flags *flags, char *out)
{
	int	val;
	int	printed;

	val = 0;
	val += (int)ft_strlen(out);
	printed = 0;
	printed += specialc(flags, 1, &val);
	printed += write(1, out, (int)ft_strlen(out));
	printed += specialc(flags, 2, &val);
	free(out);
	if (printed != val)
		return (-1);
	return (val);
}

static int	func_mapping(char c, va_list *ap, t_flags *flags)
{
	char	*out;

	out = NULL;
	if (c == 'c')
		out = ft_printf_c(va_arg(*ap, int), flags);
	else if (c == 'i' || c == 'd')
		out = ft_printf_id(va_arg(*ap, int));
	else if (c == 's')
		out = ft_printf_s(va_arg(*ap, char *), flags);
	else if (c == 'p')
		out = ft_printf_p(va_arg(*ap, void *));
	else if (c == 'u')
		out = ft_printf_u(va_arg(*ap, unsigned int));
	else if (c == 'x' || c == 'X')
		out = ft_printf_x(va_arg(*ap, unsigned int), c);
	else if (c == '%')
		out = ft_printf_percent();
	if (out && (flags->dot > -1 || flags->hash || flags->minus || flags->plus \
	|| flags->space || flags->width || flags->zero))
		out = ft_printf_filter(flags, c, out);
	return (printall(flags, out));
}

static int	str_loop(const char *str, va_list *ap, int val, t_flags *flags)
{
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			str = ft_printf_getflags(str, flags);
			val += func_mapping(*str++, ap, flags);
		}
		else
		{
			ft_putchar_fd(*str++, 1);
			val++;
		}
	}
	return (val);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_flags	flags;
	int		return_val;

	return_val = 0;
	va_start(ap, str);
	return_val = str_loop(str, &ap, return_val, &flags);
	va_end(ap);
	return (return_val);
}
