/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:10 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/16 16:11:16 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envies *new_node(char *key, char *value)
{
	t_envies	*new_node;

	new_node = malloc(sizeof(t_envies));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_command *new_com(char *com, char *args)
{
	t_command	*new_com;

	new_com = malloc(sizeof(t_command));
	new_com->command = malloc(sizeof(char *) * 2);
	if (!new_com)
		return (NULL);
	new_com->command[0] = com;
	new_com->command[1] = args;
	new_com->next = NULL;
	return (new_com);
}

int ft_com_len(t_token *stream)
{
	int i = 0;
	while (stream)
	{
		if (stream->type == PIPE)
			i++;
		stream = stream->next;
	}
	return (i);
}
