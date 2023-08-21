/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:10:47 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/21 17:05:03 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*which_token(char **str, int *exit_status)
{
	t_token	*token;
	(void)exit_status;
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
	if (token == NULL)
		*exit_status = 1;
	return (token);
}

void	tokenize(t_token **stream, char *str, int *exit_status)
{
	t_token	*tmp;
	
	tmp = NULL;
	while (*str)
	{
		(*stream) = which_token(&str, exit_status);
		if (!(*stream))
		{
			if (*exit_status != 1)
				*exit_status = 0;
			break ;
		}
		(*stream)->prev = tmp;
		tmp = (*stream);
		stream = &(*stream)->next;
	}
}
