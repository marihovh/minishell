/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_foos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:55:31 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/07 05:57:49 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_1(char **str)
{
	char	*chunk;
	int		i;
	t_token	*new;

	i = 0;
	chunk = *str;
	while (*str && *str[0] == ' ')
		(*str)++;
	chunk = ft_substr(chunk, 0, *str - chunk);
	new = new_token(SP, chunk, 0);
	return (new);
}

t_token	*token_2(char **str)
{
	char	*chunk;
	int		i;
	t_token	*new;

	i = 0;
	chunk = *str;
	while (*str && ft_isprint(*str[0]) && *str[0] != '|' \
		&& *str[0] != '>' && *str[0] != '<' && *str[0] != 39 && *str[0] != 34)
		(*str)++;
	chunk = ft_substr(chunk, 0, *str - chunk);
	new = new_token(WORD, chunk, 0);
	return (new);
}

t_token	*token_3(char **str)
{
	char	*chunk;
	t_token	*new;

	chunk = (*str);
	(*str) = ft_strchr(++chunk, 39);
	if (!(*str))
	{
		error_msg("shyshell: \': Token error", 1);
		return (NULL);
	}
	chunk = ft_substr(chunk, 0, (*str) - chunk);
	(*str)++;
	new = new_token(FIELD, chunk, 0);
	return (new);
}

t_token	*token_4(char **str)
{
	t_token	*new;
	char	*chunk;

	chunk = (*str);
	(*str) = ft_strchr(++chunk, 34);
	if (!(*str))
	{
		error_msg("shyshell: \": Token error", 1);
		return (NULL);
	}
	chunk = ft_substr(chunk, 0, (*str) - chunk);
	(*str)++;
	new = new_token(EXP_FIELD, chunk, 0);
	return (new);
}

t_token	*token_5(char **str)
{
	char	*ch;
	t_token	*new;

	(*str)++;
	if (**str == 62)
	{
		(*str) += 1;
		ch = ft_strdup(">>");
		new = new_token(REDIR_AP, ch, 1);
		return (new);
	}
	else
	{
		ch = ft_strdup(">");
		new = new_token(REDIR_OUT, ch, 1);
		return (new);
	}
	error_msg("shyshell: >: Token error", 1);
	return (NULL);
}
