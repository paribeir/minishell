/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:41:03 by jdach             #+#    #+#             */
/*   Updated: 2024/06/27 18:44:37 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- initialize history.
- start minishell loop.
- if there is input, add it to the history.
- else, print a new line.
*/

#include "minishell.h"

void	pat(void)
{
	char	*input;

	while (1)
	{
		input = readline(BLUE"Mini🐚 > "NS);
		if (*input)
		{
			add_history(input);
			tokenizer(input);
		}
		else
			write(1, "\n", 1);
	}
}
