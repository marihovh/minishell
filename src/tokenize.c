/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:10:47 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/14 17:40:35 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *which_token(char **str)
{
	t_token *token;
	
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
	else if (ft_isspace(*str[0]))
		token = token_1(str);
	else
		error_msg("Token error\n");
	return (token);
}

void tokenize(t_token **stream, char *str)
{
	t_token *tmp;
	
	tmp = NULL;
	while (*str)
	{
		(*stream) = which_token(&str);
		if (!(*stream))
			break ;
		if (tmp)
			(*stream)->prev = tmp;
		else
			(*stream)->prev = NULL;
		tmp = (*stream);
		// printf("<%s>\n", (*stream)->value);
		stream = &(*stream)->next;
	}
}