/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 05:37:13 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:40:31 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_to_value(t_export **export, char *key, char *value)
{
	while ((*export))
	{
		if (!ft_strcmp(key, (*export)->key))
		{
			(*export)->value = ft_strjoin((*export)->value, value);
			return ;
		}
		export = &(*export)->next;
	}
}

void	update_exp_value(t_export **export, char *key, char *value)
{
	while ((*export))
	{
		if (!ft_strcmp(key, (*export)->key))
		{
			free((*export)->value);
			(*export)->value = ft_strdup(value);
			return ;
		}
		export = &(*export)->next;
	}
}

int	is_export(t_export **export, char *str)
{
	while ((*export))
	{
		if (!ft_strcmp(str, (*export)->key))
			return (1);
		export = &(*export)->next;
	}
	return (0);
}

t_export	*new_expo_node(char *key, char *value)
{
	t_export	*new_node;

	new_node = malloc(sizeof(t_export));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	to_env(t_envies **env, char *key, char *value)
{
	char	*tmp;

	tmp = find_env(env, key);
	if (tmp)
	{
		free(tmp);
		update_env_value(env, key, value);
		return ;
	}
	while ((*env))
		env = &(*env)->next;
	(*env) = new_node(key, value);
	env = &(*env)->next;
}
