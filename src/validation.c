/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:47:33 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/17 19:57:16 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_error(void)
{
	printf("syntax error near unexpected token `newline'\n");
	return (0);
}

void	open_eror(void)
{
	printf("cant open");
	exit(1);
}

int validation(t_token *stream)
{
	(void)stream;
	// while (stream)
	// {
	// 	if (stream->type == PIPE)
	// 	{
	// 		if (stream->prev == NULL || stream->next == NULL)
	// 		{
	// 			printf("pipe error broo\n");
	// 			return (0);
	// 		}else if (stream->prev->type == SP && (stream->prev->prev == NULL || stream->prev->prev->type != WORD))
	// 		{
	// 			printf("pipe error yooo\n");
	// 			return (0);
	// 		}
	// 	}else if (stream->type == REDIR_OUT || stream->type == REDIR_IN || stream->type == REDIR_AP || stream->type == REDIR_SO)
	// 	{
	// 		if (stream->next == NULL)
	// 			redir_error();
	// 		// else if(stream->prev->type == SP && (stream->prev->prev == NULL || stream->prev->prev->type != WORD))
	// 			// redir_error();
	// 	}
	// 	stream = stream->next;
	// }
	return (1);
}
