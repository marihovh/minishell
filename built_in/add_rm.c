/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:00:18 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/24 00:27:50 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int first_char(char ch)
{
	return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_');
}

int other_char(char ch)
{
	return (first_char(ch) || (ch >= '0' && ch <= '9'));
}

char *valid_key(char *command, int *flag)
{
	char	*key;
	int		i;

	i = 0;
	key = f_k(command, flag);
	if (!key)
		return (0);
	while (key[i])
	{
		if (i == 0 && first_char(key[i]))
			i++;
		else if (i != 0 && other_char(key[i]))
			i++;
		else
		{
			ft_putstr_fd("shyshell : export: `", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			g_exit_statuss = 1;
			free(key);
			return (NULL);
		}
		i++;
	}
	return (key);
}

int	add_exp(t_command *node, t_export **export, t_envies **env)
{
	char	*value;
	char	*key;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (node->command[++i])
	{
		key = valid_key(node->command[i], &flag);
		if (!key)
			return (1);
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
	return (0);
}

int	ft_export(t_command *node, t_data *data)
{
	int	i;

	i = 0;
	if (!(node->command[++i]))
		printing_export(data->export);
	add_exp(node, &data->export, &data->envies);	
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

int	ft_unset(t_command *node, t_envies *env, t_export *export)
{
	int	i;

	i = 1;
	while (node->command[i])
	{
		env_delete(&env, node->command[i]);
		export_delete(&export, node->command[i]);
		i++;
	}
	return (g_exit_statuss);
}
