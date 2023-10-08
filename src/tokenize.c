/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:10:47 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:31:41 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*which_token(char **str)
{
	t_token	*token;

	token = NULL;
	if (*str[0] == '|')
		token = token_9(str);
	else if (*str[0] == 39)
		token = token_3(str);
	else if (*str[0] == '>')
		token = token_5(str);
	else if (*str[0] == '<')
		token = token_6(str);
	else if (*str[0] == 34)
		token = token_4(str);
	else if (ft_isprint(*str[0]))
		token = token_2(str);
	else if (*str[0] == ' ')
		token = token_1(str);
	if (token == NULL)
		g_exit_statuss = 1;
	return (token);
}

int	tokenize(t_token **stream, char *str, int *cnt)
{
	t_token	*tmp;

	*cnt = 0;
	tmp = NULL;
	while (*str)
	{
		(*stream) = which_token(&str);
		if (!(*stream))
		{
			if (g_exit_statuss != 1)
				g_exit_statuss = 0;
			else
				return (1);
			break ;
		}
		(*stream)->prev = tmp;
		tmp = (*stream);
		(*cnt)++;
		stream = &(*stream)->next;
	}
	return (0);
}
