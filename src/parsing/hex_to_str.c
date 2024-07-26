/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:24:23 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/26 18:45:17 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ptr_to_str(unsigned long number) 
{
	char *str;
	unsigned long temp;
	char *end;
	int len;

	len = 0;
	if (number == 0) 
	{
		str = (char *)ft_calloc(2, 1);
		if (str == NULL) 
		{
			ft_printf("malloc error\n");
			return (NULL);
		}
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	temp = number;
	while (temp > 0) 
	{
		temp /= 10;
		len++;
	}
	str = (char *)ft_calloc(len + 1, 1);
	if (str == NULL) 
	{
		ft_printf("malloc error\n");
		return (NULL);
	}
	end = str + len;
	*end = '\0';
	while (number > 0) 
	{
		*(--end) = (number % 10) + '0';
		number /= 10;
	}
	return (str);
}

char	*hex_to_dec(void *ptr)
{
	unsigned long value;
	char *str;
	char	*temp;

	value = (unsigned long)ptr;
	str = ptr_to_str(value);

	temp = str;
	str = ft_strjoin("here_doc_temp_", str);
	free (temp);
	return (str);
}
