/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:47:33 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/15 14:23:54 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_eror(void)
{
	printf("cant open");
	exit(1);
}

int pipe_parse(t_token *stream)
{
	if ((stream->prev == NULL || stream->next == NULL) \
		|| (stream->next->type == PIPE) \
		|| (stream->prev->type == SP && (stream->prev->prev == NULL)) \
		|| (stream->next->type == SP && (stream->next->next == NULL)))
	{
		g_exit_statuss = 1;
		return (1);
	}
	else
		g_exit_statuss = 0;
	return (0);
}

int red_parse(t_token *stream)
{
	if (stream->next == NULL ||  (stream->next->type == SP && !stream->next->next))
	{
		printf("shyshell: syntax error near unexpected token `newline'\n");
		g_exit_statuss = 1;
		return (1);
	}else if (stream->next->type != WORD && stream->next->type != SP \
		&& stream->next->type != EXP_FIELD && stream->next->type != FIELD)
	{
		printf("shyshell: syntax error near unexpected token `%s'\n", stream->next->value);
		g_exit_statuss = 1;
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

void	join_field(t_token **stream)
{
	char *tmp;
    t_token *nextNode;

	tmp = ft_strjoin((*stream)->value, (*stream)->next->value);
	(*stream)->value = ft_strdup(tmp);
	if ((*stream)->next->next == NULL)
	{
		free((*stream)->next->value);
		free((*stream)->next);
		(*stream)->next = NULL;
		return ;
	}
	nextNode = (*stream)->next->next;
	free((*stream)->next->value);
	free((*stream)->next);
	(*stream)->next = nextNode;
}

int validation(t_token *stream)
{
	while (stream)
	{
		if (stream->type == WORD || stream->type == EXP_FIELD || stream->type == FIELD)
		{
			if (stream->next && (stream->next->type == WORD || stream->next->type == EXP_FIELD || stream->next->type == FIELD))
				join_field(&stream);
		}
		else if (stream->type == SP)
		{
			if (stream->prev == NULL && stream->next == NULL)
			{
				g_exit_statuss = 0;
				return (1);
			}
		}
		else if (stream->type == PIPE)
		{
			if (pipe_parse(stream))
			{
				printf("syntax error near unexpected token `|'\n");
				g_exit_statuss = 258;
				return (1);
			}
		}else if (stream->op)
		{
			if (red_parse(stream))
			{
				g_exit_statuss = 258;
				return (1);
			}
		}
		stream = stream->next;
	}
	if (here_doc_cnt(stream) > 16)
		return (1);
	return (0);
}
