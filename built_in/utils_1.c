/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 05:39:27 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/28 22:30:11 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_delete(t_export **export, char *node)
{
	t_export	*current;
	t_export	*prev;

	prev = NULL;
	current = *export;
	while (current)
	{
		if (!ft_strcmp(node, current->key))
		{
			if (prev == NULL)
				*export = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	helpp(t_export **export, char *key, char *value, int flag)
{
	if (flag == 1)
		join_to_value(export, key, value);
	else
		update_exp_value(export, key, value);
}

void	free_kv(char *key, char *value)
{
	if (key && !value)
		free(key);
	if (key && value)
	{
		free(key);
		free(value);
	}
}
