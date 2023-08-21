/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_foos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:55:31 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/21 16:59:24 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_1(char **str)
{
	char	*chunk;
	int		i;

	i = 0;
	chunk = *str;
	while (*str && ft_isspace(*str[0]))
		(*str)++;
	chunk = ft_substr(chunk, 0, *str - chunk);
	return (new_token(SP, chunk, 0));
}

t_token	*token_2(char **str)
{
	char	*chunk;
	int		i;

	i = 0;
	chunk = *str;
	while (*str && ft_isprint(*str[0]) && *str[0] != '|' \
		&& *str[0] != '>' && *str[0] != '<' && *str[0] != 39 && *str[0] != 34)
		(*str)++;
	chunk = ft_substr(chunk, 0, *str - chunk);
	return (new_token(WORD, chunk, 0));
}

t_token	*token_3(char **str)
{
	char	*chunk;

	chunk = (*str);
	(*str) = ft_strchr(++chunk, 39);
	if (!(*str))
	{
		
		error_msg("Token error\n");
		return (NULL);
	}
	chunk = ft_substr(chunk, 0, (*str) - chunk);
	(*str)++;
	return (new_token(FIELD, chunk, 0));
}

t_token	*token_4(char **str)
{
	char	*chunk;

	chunk = (*str);
	(*str) = ft_strchr(++chunk, 34);
	if (!(*str))
	{
		error_msg("Token error\n");
		return (NULL);
	}
	chunk = ft_substr(chunk, 0, (*str) - chunk);
	(*str)++;
	return (new_token(EXP_FIELD, chunk, 0));
}

t_token	*token_5(char **str)
{
	(*str)++;
	if (**str == 62)
	{
		(*str) += 1;
		return (new_token(REDIR_AP, ">>", 1));
	}
	else
		return (new_token(REDIR_OUT, ">", 1));
	error_msg("Token error\n");
	return (NULL);
}
