/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:47:33 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/16 19:51:15 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void validation(t_token *stream)
{
	while (stream)
	{
		if (stream->type == PIPE)
		{
			if (stream->prev == NULL || stream->next == NULL)
			{
				printf("pipe error broo\n");
				exit(1);
			}else if (stream->prev->type == SP && (stream->prev->prev == NULL || stream->prev->prev->type != WORD))
			{
				printf("pipe error yooo\n");
				exit(1);
			}
		}else if (stream->type == REDIR_OUT || stream->type == REDIR_IN || stream->type == REDIR_AP || stream->type == REDIR_SO)
		{
			if (stream->prev == NULL || stream->next == NULL)
			{
				printf("redirection error broo\n");
				exit(1);
			}else if (stream->prev->type == SP && (stream->prev->prev == NULL || stream->prev->prev->type != WORD))
			{
				printf("redirection error yooo\n");
				exit(1);
			}
		}
		stream = stream->next;
	}
}