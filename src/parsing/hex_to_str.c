/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:24:23 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/08 20:02:40 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle zero case
char	*handle_zero_case(void) 
{
	char	*str;
	
	str = (char *)ft_calloc(2, 1);
	if (str == NULL) 
	{
		ft_printf("malloc error\n");
		return (NULL);
	}
	str[0] = '0';
	return (str);
}

//calculate the length of the string required to store the number
int	calculate_length(unsigned long number) 
{
	int len;
	unsigned long temp;
	
	len = 0;
	temp = number;
	while (temp > 0) 
	{
		temp /= 10;
		len++;
	}
	return (len);
}

//convert nbr to string
void	convert_to_string(char *str, unsigned long number, int len) 
{
	char	*end;

	end = str + len;
	*end = '\0';
	while (number > 0) 
	{
		*(--end) = (number % 10) + '0';
		number /= 10;
	}
}

char	*ptr_to_str(unsigned long number) 
{
	int	len;
	char	*str;
	
	if (number == 0) 
		return handle_zero_case();	
	len = calculate_length(number);
	str = (char *)ft_calloc(len + 1, 1);
	if (str == NULL) 
	{
		ft_printf("malloc error\n");
		return (NULL);
	}
	convert_to_string(str, number, len);
	return (str);
}

char	*hex_to_dec(void *ptr)
{
	unsigned long	value;
	char			*str;
	char			*temp;

	value = (unsigned long)ptr;
	str = ptr_to_str(value);
	if (str == NULL)  // Check if ptr_to_str failed
		return (NULL);

	temp = str;
	str = ft_strjoin("here_doc_temp_", str);
	if (str == NULL)  // Check if ft_strjoin failed
	{
		free(temp);  // Clean up original memory before returning NULL
		return (NULL);
	}
	free(temp);  // Free the original string now that the new string is allocated
	return (str);
}
