/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:47:33 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 18:40:52 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_parse(t_token *stream)
{
	if ((stream->prev == NULL || stream->next == NULL) \
		|| (stream->next->type == PIPE) \
		|| (stream->prev->type == SP && (stream->prev->prev == NULL)) \
		|| (stream->next->type == SP && (stream->next->next == NULL)))
		return (1);
	return (0);
}

int	red_parse(t_token *stream)
{
	if (stream->next == NULL \
		|| (stream->next->type == SP && !stream->next->next))
	{
		ft_putstr_fd("shyshell: syntax error near", 2);
		ft_putstr_fd(" unexpected token `newline\'\n", 2);
		g_exit_statuss = 258;
		return (1);
	}
	else if (stream->next->type != WORD && stream->next->type != SP \
		&& stream->next->type != EXP_FIELD && stream->next->type != FIELD)
	{
		write(2, "shyshell: syntax error near unexpected token `", 45);
		write(2, stream->next->value, ft_strlen(stream->next->value));
		write(2, "'\n", 2);
		return (1);
	}
	return (0);
}

void	join_field(t_token **stream)
{
	char	*tmp;
	t_token	*next_node;

	tmp = ft_strjoin((*stream)->value, (*stream)->next->value);
	(*stream)->value = ft_strdup(tmp);
	free(tmp);
	if ((*stream)->next->next == NULL)
	{
		free((*stream)->next->value);
		free((*stream)->next);
		(*stream)->next = NULL;
		return ;
	}
	next_node = (*stream)->next->next;
	free((*stream)->next->value);
	free((*stream)->next);
	(*stream)->next = next_node;
}

int	validation_2(t_token *stream)
{
	if (stream->type == PIPE)
	{
		if (pipe_parse(stream))
		{
			printf("syntax error near unexpected token `|'\n");
			g_exit_statuss = 258;
			return (1);
		}
	}
	else if (stream->op)
	{
		if (red_parse(stream))
		{
			g_exit_statuss = 258;
			return (1);
		}
	}
	return (0);
}

int	validation(t_token *stream)
{
	while (stream)
	{
		if (stream->type == WORD || stream->type == EXP_FIELD \
			|| stream->type == FIELD)
		{
			if (stream->next && (stream->next->type == WORD \
				|| stream->next->type == EXP_FIELD \
				|| stream->next->type == FIELD))
			{
				join_field(&stream);
				continue ;
			}
		}
		else if (stream->type == SP)
		{
			if (stream->prev == NULL && stream->next == NULL)
				return (valid_helper());
		}
		if (validation_2(stream))
			return (1);
		stream = stream->next;
	}
	return (0);
}
