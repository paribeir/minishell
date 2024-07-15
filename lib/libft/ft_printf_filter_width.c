/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_filter_width.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:00:45 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 17:03:45 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*string_minus(char pad_char, int width, char *out, char c)
{
	char	*new_string;
	int		i;
	int		out_length;

	out_length = (int)ft_strlen(out);
	i = 0;
	new_string = malloc(width * sizeof(char));
	if (!new_string)
		return (NULL);
	ft_strlcpy(&new_string[i], out, (out_length + 1));
	while (out_length < width - 1 && c != '%')
		new_string[out_length++] = pad_char;
	new_string[out_length] = '\0';
	free(out);
	return (new_string);
}

static char	*string(char pad_char, int width, char *out, char c)
{
	char	*new_string;
	int		i;
	int		j;
	int		out_length;

	out_length = (int)ft_strlen(out);
	i = 0;
	j = 0;
	new_string = malloc(width * sizeof(char));
	if (!new_string)
		return (NULL);
	if ((c == 'i' || c == 'd') && (out[j] == '-' || out[j] == '+') \
	&& pad_char == '0')
		new_string[i++] = out[j++];
	while (out_length++ < width - 1 && c != '%')
		new_string[i++] = pad_char;
	ft_strlcpy(&new_string[i], &out[j], (out_length + 1));
	free(out);
	return (new_string);
}

char	*ft_printf_filter_width(t_flags *flags, char *out, char c)
{
	char	pad_char;
	int		extra_width;

	pad_char = ' ';
	extra_width = flags->width + 1;
	if (flags->specialc == 1)
		extra_width = flags->width;
	if (flags->zero == 1 && flags->dot == -1 && flags->minus == 0)
		pad_char = '0';
	if (flags->minus == 1)
		return (string_minus(pad_char, extra_width, out, c));
	else
		return (string(pad_char, extra_width, out, c));
}
