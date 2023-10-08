/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:04:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:10:29 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prin(t_token *stream, t_command *com_stream)
{
	int	i;

	i = -1;
	if (!stream)
		return ;
	while (stream)
	{
		printf("stream:{%s}\n", stream->value);
		printf("type:%i\n", stream->type);
		printf("in:%i\n", stream->in);
		printf("out:%i\n", stream->out);
		stream = stream->next;
	}
	while (com_stream)
	{
		printf("command:");
		i = -1;
		while (com_stream->command[++i])
		{
			printf("{%s}", com_stream->command[i]);
			printf("%i, %i\n", com_stream->in, com_stream->out);
		}
		printf("\n");
		com_stream = com_stream->next;
	}
}

void	pri(t_command *com_stream)
{
	while (com_stream)
	{
		printf("command:%s\n", com_stream->command[0]);
		printf("in:%i   out:%i\n", com_stream->in, com_stream->out);
		com_stream = com_stream->next;
	}
}

void	print_en(t_envies *envies)
{
	while (envies)
	{
		printf("%s=%s\n", envies->key, envies->value);
		envies = envies->next;
	}
}
