/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:08:29 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:35:21 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_coms(t_command *stream)
{
	t_command	*current;
	t_command	*next_node;
	int			i;

	current = stream;
	while (current != NULL)
	{
		next_node = current->next;
		i = -1;
		while (current->command[++i])
			free(current->command[i]);
		free(current->command);
		free(current);
		current = next_node;
	}
}

void	free_tokens(t_token *stream)
{
	t_token	*current;
	t_token	*next_node;

	current = stream;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->value);
		free(current);
		current = next_node;
	}
}

void	soo_word(t_token **tmp)
{
	while (*tmp && ((*tmp)->type != PIPE && (*tmp)->type != WORD \
		&& (*tmp)->type != FIELD && (*tmp)->type != EXP_FIELD))
		(*tmp) = (*tmp)->next;
}

int	normalize(t_token **stream)
{
	t_token	*com;

	while (*stream)
	{
		if ((*stream)->op == 1)
		{
			com = (*stream);
			if ((com)->prev)
				while (com && ((com)->type != PIPE && com->type != WORD \
					&& com->type != FIELD && com->type != EXP_FIELD))
					com = com->prev;
			if (!com || com->op == 1 || (com)->type == PIPE)
			{
				(*stream) = try(stream);
				if ((*stream)->op == 1)
					return (0);
			}
			com = NULL;
		}
		stream = &(*stream)->next;
	}
	return (1);
}

t_token	*find_com(t_token **stream, int fd, int fedo)
{
	t_token	*com;
	t_token	*tmp;
	t_token	*redir;

	if ((*stream)->prev)
		com = (*stream)->prev;
	else
		return (0);
	redir = (*stream);
	if ((*stream)->next)
		tmp = (*stream)->next;
	else
		tmp = (*stream);
	if ((com)->prev)
		while (com && ((com)->type != PIPE && com->type != WORD \
			&& com->type != FIELD && com->type != EXP_FIELD))
			com = com->prev;
	soo_word(&tmp);
	if (com && (com != (*stream) || com->type == PIPE))
	{
		com->next = NULL;
		com->next = tmp->next;
	}
	if (tmp->next != NULL)
		tmp->next->prev = com;
	else
		com->next = NULL;
	(*stream) = redir;
	find_com_2(stream, tmp, com);
	if ((com)->type != PIPE)
		set_fd(&com, fd, fedo);
	return (com);
}
