/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:00:18 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:48:03 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*valid_key(char *command, int *flag, char *what)
{
	char	*key;
	int		i;

	i = 0;
	key = f_k(command, flag);
	if (!key[0])
	{
		exp_error(what, command);
		g_exit_statuss = 1;
		free(key);
		return (0);
	}
	while (key[i])
	{
		if (i == 0 && first_char(key[i]))
			i++;
		else if (i != 0 && other_char(key[i]))
			i++;
		else
		{
			exp_error(what, key);
			g_exit_statuss = 1;
			free(key);
			return (NULL);
		}
	}
	return (key);
}

void	add_exp(t_command *node, t_export **export, t_envies **env, int flag)
{
	char	*value;
	char	*key;
	int		i;

	i = 0;
	while (node->command[++i])
	{
		key = valid_key(node->command[i], &flag, "export");
		if (!key)
			return ;
		value = f_v(node->command[i]);
		if (value != NULL)
			to_env(env, key, value);
		if (is_export(export, key))
			helpp(export, key, value, flag);
		else
		{
			while ((*export))
				export = &(*export)->next;
			(*export) = new_expo_node(key, value);
			export = &(*export)->next;
		}
		free_kv(key, value);
	}
}

int	ft_export(t_command *node, t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!(node->command[++i]))
		printing_export(data->export);
	add_exp(node, &data->export, &data->envies, flag);
	return (0);
}

void	fill_the_export(t_export **export, t_envies *env)
{
	while (env != NULL)
	{
		(*export) = new_expo_node(env->key, env->value);
		if (!(*export))
			break ;
		export = &(*export)->next;
		env = env->next;
	}
	(*export) = new_expo_node("OLDPWD", NULL);
	export = &(*export)->next;
}

void	env_delete(t_envies **env, char	*node)
{
	t_envies	*current;
	t_envies	*prev;

	prev = NULL;
	current = *env;
	while (current)
	{
		if (!ft_strcmp(node, current->key))
		{
			if (prev == NULL)
				*env = current->next;
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
