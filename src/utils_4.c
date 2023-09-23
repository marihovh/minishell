/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:08:29 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 11:32:10 by marihovh         ###   ########.fr       */
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
