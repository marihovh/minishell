/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:47:33 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/18 20:28:19 by marihovh         ###   ########.fr       */
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

int pipe_parse(t_token *stream, int *exit_status)
{
	if ((stream->prev == NULL || stream->next == NULL) \
		|| (stream->next->type == PIPE) \
		|| (stream->prev->type == SP && (stream->prev->prev == NULL || stream->prev->prev->type != WORD)) \
		|| (stream->next->type == SP && (stream->next->next == NULL || stream->next->next->type != WORD)))
	{
		*exit_status = 1;
		return (1);
	}
	else
		*exit_status = 0;
	return (0);
}

int red_parse(t_token *stream, int *exit_status)
{
	if (stream->next == NULL || (stream->next->type == SP && stream->next->next->type != WORD))
	{
		*exit_status = 1;
		return (1);
	}
	else
		*exit_status = 0;
	return (0);
}

int here_doc_cnt(t_token *stream)
{
	int i = 0;
	while (stream)
	{
		if (stream->type == REDIR_SO)
			i++;
		stream = stream->next;
	}
	return (i);
}

int validation(t_token *stream, int *exit_status)
{
	while (stream)
	{
		if (stream->type == SP)
		{
			if (stream->prev == NULL && stream->next == NULL)
			{
				*exit_status = 0;
				return (1);
			}
		}
		else if (stream->type == PIPE)
		{
			if (pipe_parse(stream, exit_status))
			{
				printf("syntax error near unexpected token `|'\n");
				return (1);
			}
		}else if (stream->type == REDIR_OUT || stream->type == REDIR_IN || stream->type == REDIR_AP || stream->type == REDIR_SO)
		{
			if (red_parse(stream, exit_status))
			{
				printf("syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		stream = stream->next;
	}
	if (here_doc_cnt(stream) > 16)
		return (1);
	return (0);
}
