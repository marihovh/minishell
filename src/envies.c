/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envies.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:07:53 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/28 19:28:42 by marihovh         ###   ########.fr       */
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

void init_env(t_envies **envp, char **environ)
{
	char *str;
	char *chunk;
	int	i;

	i = -1;
	while (environ[++i])
	{
		str = ft_strchr(environ[i], '=');
		if (!str)
			break ;
		chunk = ft_substr(environ[i], 0, str - environ[i]);
		if (!chunk)
			break ;
		(*envp) = new_node(chunk, str + 1);
		if (!(*envp))
			break ;
		envp = &(*envp)->next;
	}
}