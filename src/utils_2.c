/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:24:27 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/24 13:37:23 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_6(char **str)
{
	char *ch;
	(*str)++;
	if (**str == 60)
	{
		(*str) += 1;
		ch = ft_strdup("<<");
		return (new_token(REDIR_SO, ch, 1));
	}
	else
	{
		ch = ft_strdup("<");
		return (new_token(REDIR_IN, ch, 1));
	}
	error_msg("Token error\n");
	return (0);
}

t_token	*token_9(char **str)
{
	char *ch;
	(*str)++;
	ch = ft_strdup("|");
	return (new_token(PIPE, ch, 0));
}
