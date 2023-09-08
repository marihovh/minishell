/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:00:18 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/07 18:07:25 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int add_exp(t_command *node, t_export **export, t_envies **env)
{
	(void)env;
	int i = 1;
	while((*export)->next)
		export = &(*export)->next;
	while((*env)->next)
		env = &(*env)->next;
	while(node->command[i])
	{
		if((f_v(node->command[i])))
		{
			(*env) = new_node(f_k(node->command[i]),f_v(node->command[i]));
			env = &(*env)->next;
		}
		(*export) = new_expo_node(f_k(node->command[i]),f_v(node->command[i]),"declare -x ");
		export = &(*export)->next;
		i++;
	}
	return (0);
}

int ft_export(t_command *node, t_data *data)
{
	int i = 0;
	if(!(node->command[++i]))
	{
		printing_export(data->export);
		return(0);
	}
	add_exp(node, &data->export, &data->envies);
	// printing_export(data);
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


t_export	*new_expo_node(char *key, char *value, char *def)
{
	t_export	*new_node;

	new_node = malloc(sizeof(t_export));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->def = ft_strdup(def);
	new_node->next = NULL;
	return (new_node);
}


void	fill_the_export(t_export **export, t_envies *env)
{
	while(env != NULL)
	{
		(*export) = new_expo_node(env->key, env->value, "declare -x ");
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
	return (node->exit_status);
}