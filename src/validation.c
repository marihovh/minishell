/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:47:33 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/30 15:16:59 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_eror(void)
{
	printf("cant open");
	exit(1);
}

int pipe_parse(t_token *stream, int *exit_status)
{
	if ((stream->prev == NULL || stream->next == NULL) \
		|| (stream->next->type == PIPE) \
		|| (stream->prev->type == SP && (stream->prev->prev == NULL)) \
		|| (stream->next->type == SP && (stream->next->next == NULL)))
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
	if (stream->next == NULL ||  (stream->next->type == SP && !stream->next->next))
	{
		printf("shyshell: syntax error near unexpected token `newline'\n");
		*exit_status = 1;
		return (1);
	}else if (stream->next->type != WORD && stream->next->type != SP \
		&& stream->next->type != EXP_FIELD && stream->next->type != FIELD)
	{
		printf("shyshell: syntax error near unexpected token `%s'\n", stream->next->value);
		*exit_status = 1;
		return (1);
	}
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
				*exit_status = 258;
				return (1);
			}
		}else if (stream->type == REDIR_OUT || stream->type == REDIR_IN || stream->type == REDIR_AP || stream->type == REDIR_SO)
		{
			if (red_parse(stream, exit_status))
			{
				*exit_status = 258;
				return (1);
			}
		}
		stream = stream->next;
	}
	if (here_doc_cnt(stream) > 16)
		return (1);
	return (0);
}
