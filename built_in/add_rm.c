/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:00:18 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/18 20:12:18 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_export(t_export **export, char *str)
{
	while ((*export))
	{
		if (!ft_strcmp(str, (*export)->key))
			return (1);
		export = &(*export)->next;
	}
	return (0);
}

void join_to_value(t_export **export, char *key, char *value)
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

void update_value(t_export **export, char *key, char *value)
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

int add_exp(t_command *node, t_export **export, t_envies **env)
{
	char *value;
	char *key;
	int flag = 0;
	int i = 1;
	while((*env))
		env = &(*env)->next;
	while(node->command[i])
	{
		key = f_k(node->command[i], &flag);
		value = f_v(node->command[i]);
		if (value)
		{
			(*env) = new_node(key, value);
			env = &(*env)->next;
		}
		if (is_export(export, key))
		{
			if (flag == 1)
				join_to_value(export, key, value);
			else
				update_value(export, key, value);
		}
		else
		{
			while((*export))
				export = &(*export)->next;
			(*export) = new_expo_node(key, value);
			export = &(*export)->next;
		}
		free(key);
		free(value);
		i++;
	}
	return (0);
}

int ft_export(t_command *node, t_data *data)
{
	int i = 0;
	if(!(node->command[++i]))
		printing_export(data->export);
	add_exp(node, &data->export, &data->envies);
	return (0);
}

// kareli e jnjel

// int ft_exxport(t_command *node, t_data *data, t_export **export, t_envies **env)
// {
// 	int	i;
// 	// int	j;
// 	(void)env;
// 	i = 0;
// 	if(!(node->command[++i]))
// 	{
// 		printing_export(data);
// 	// printf("aaa:%s\n", (*export)->next->key);
// 		return(0);
// 	}
// 	while((*export)->next)
// 		export = &(*export)->next;
// 	// while((*data)->envies)
// 	// 	(*data)->envies = (*data)->envies->next;
// 	while(node->command[i])
// 	{
// 		// if((f_v(node->command[i])))
// 		// 	(*data)->envies = new_node(f_k(node->command[i]),f_v(node->command[i]));
// 		// printf("aaa:%s\n", (*export)->key);
// 		(*export) = new_expo_node(f_k(node->command[i]),f_v(node->command[i]),"declare - x ");
// 		i++;
// 	}
// 	// printf("aaa:%s\n", (*export)->next->key);
// 	return (0);
// }

void	delete_node(t_envies **env, char *del_node)
{
	t_envies *head;
	t_envies *prev;

	head = (*env);
	prev = NULL;
	while(head != NULL)
	{
	if (ft_strcmp(head->key , del_node) == 0)
		{
		if(prev == NULL)
			*(env) = head->next;
		else
			prev->next = head->next;
		free(head);
		free(head->key);
		free(head->value);
		}
	}
	prev = head;
	head = head->next;
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


void	fill_the_export(t_export **export, t_envies *env)
{
	while(env != NULL)
	{
		(*export) = new_expo_node(env->key, env->value);
		if (!(*export))
			break ;
		export = &(*export)->next;
		env = env->next;
	}
}

int ft_unset(t_command *node, t_envies *env)
{
	int			i;
	t_envies	*tmp;

	i = 0;
	tmp = env;
	while(node->command[++i] && env->next)
	{
		if(!(ft_strcmp(node->command[i] , env->key)))
			delete_node(&(env),(env->value));
		env = env->next;	
	}
	env = tmp;
	return (g_exit_statuss);
}