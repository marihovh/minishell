/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/04 17:43:21 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_spl(char **splited)
{
	int	k;

	k = -1;
	while (splited && splited[++k])
	{
		free(splited[k]);
		splited[k] = NULL;
	}
	free(splited);
}

void	to_struct(t_data *data, t_command **com_stream)
{
	int pip_cnt;
	t_token *tmp;
	char **command;
	t_token *eee;
	t_command *pre = NULL;

	eee = data->stream;
	pip_cnt = ft_com_len(data) + 1;
	while (pip_cnt--)
	{
		command = init_com(&data->stream);
		tmp = data->stream;
		if (tmp->prev &&  tmp->prev->type == WORD)
			tmp = tmp->prev;
		else if (data->stream->next && data->stream->next->type == PIPE)
			tmp = data->stream;
		(*com_stream) = new_com(command, tmp->in, tmp->out);
		if (data->stream)
			data->stream = data->stream->next;
		if (!(*com_stream))
			break ;
		(*com_stream)->prev = pre;
		pre = (*com_stream);
		com_stream = &(*com_stream)->next;
	}
	data->stream = eee;
}


int ft_arg_len(t_token *stream)
{
	int i = 0;

	while (stream && stream->type != PIPE)
	{
		if (stream->type == WORD || stream->type == FIELD)
			i++;
		stream = stream->next;
	}
	return (i);
}

char **init_com(t_token **stream)
{
	char **command;
	int len;
	int i;

	i = 0;
	if ((*stream) && (*stream)->type == PIPE)
		(*stream) = (*stream)->next;
	len  = ft_arg_len((*stream));
	command = malloc(sizeof(char *) * (len + 1));
	while ((*stream) && (*stream)->type != PIPE)
	{
		if ((*stream)->type == WORD || (*stream)->type == FIELD)
			command[i++] = ft_strdup((*stream)->value);
		if ((*stream)->next == NULL || (*stream)->next->type == PIPE)
			break ;
		(*stream) = (*stream)->next;
	}
	command[i] = NULL;
	// i = -1;
	// while (command[++i])
	// 	printf("com:%s\n", command[i]);
	// printf("as:{%s}\n", (*stream)->value);
	return (command);
}
