/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_filter_dot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:20:19 by jdach             #+#    #+#             */
/*   Updated: 2024/01/20 17:02:46 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*filter_dot_s(t_flags *flags, char *out)
{
	char	*new_string;

	if (flags->dot < (int)ft_strlen(out))
	{
		new_string = ft_substr(out, 0, flags->dot);
		free (out);
		return (new_string);
	}
	return (out);
}

static int	calc_extra_width(t_flags *flags, char *out)
{
	int	extra_width;

	if (*out == '-' || *out == '+')
		extra_width = (flags->dot + 1) - (int)ft_strlen(out);
	else
		extra_width = flags->dot - (int)ft_strlen(out);
	return (extra_width);
}

static char	*string_without_zero(char *out)
{
	char	*new_string;

	if (out[0] == '+')
	{
		new_string = malloc(2 * sizeof(char));
		if (!new_string)
			return (NULL);
		new_string[0] = '+';
		new_string[1] = '\0';
	}
	else
	{
		new_string = malloc(1 * sizeof(char));
		if (!new_string)
			return (NULL);
		new_string[0] = '\0';
	}
	free(out);
	return (new_string);
}

static char	*return_string(t_flags *flags, char *out)
{
	char	*new_string;
	int		extra_width;
	int		i;
	int		j;

	i = 0;
	j = 0;
	extra_width = calc_extra_width(flags, out);
	new_string = malloc((flags->dot + 2) * sizeof(char));
	if (!new_string)
		return (NULL);
	if (*out == '-' || *out == '+')
		new_string[i++] = out[j++];
	while (extra_width-- > 0)
		new_string[i++] = '0';
	ft_strlcpy(&new_string[i], &out[j], ((int)ft_strlen(out) + 1));
	free (out);
	return (new_string);
}

char	*ft_printf_filter_dot(t_flags *flags, char *out, char c)
{
	if (c == 's')
		return (filter_dot_s(flags, out));
	if (flags->dot == 0 && ((out[0] == '0' && out[1] == '\0') || \
	(out[0] == '+' && out[1] == '0' && out[2] == '\0')))
		return (string_without_zero(out));
	if (calc_extra_width(flags, out) > 0)
		return (return_string(flags, out));
	return (out);
}
