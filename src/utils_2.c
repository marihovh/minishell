/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:24:27 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/07 20:27:07 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_6(char **str)
{
	if (**str == 60)
	{
		(*str) += 1;
		return (new_token(REDIR_IN, "<", 1));
	}
	else
	{
		(*str) += 2;
		return (new_token(REDIR_SO, "<<", 1));
	}
	error_msg("Token error\n");
	return (0);
}

t_token	*token_9(char **str)
{
	(*str)++;
	return (new_token(PIPE, "|", 0));
}
