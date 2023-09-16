/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impliment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/15 16:23:03 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_built_in(t_command *node)
{
	if(!(ft_strcmp_up("echo", node->command[0])))
	{
		return (1);
	}
	else if(!(ft_strcmp("pwd", node->command[0])))
		return (1);
	else if(!(ft_strcmp("cd", node->command[0])))
		return (1);
	else if(!(ft_strcmp("env", node->command[0])))
		return (1);
	else if(!(ft_strcmp("exit", node->command[0])))
		return (1);
	else if(!(ft_strcmp("export", node->command[0])))
		return (1);
	else if(!(ft_strcmp("unset", node->command[0])))
		return (1);
	return (0);
}

int	built_in(t_command *node, t_data *data,t_envies *env)
{
	(void)data;
	if(!(ft_strcmp_up("echo", node->command[0])))
		ft_echo(node);
	else if(!(ft_strcmp("pwd", node->command[0])))
		ft_pwd(node);
	else if(!(ft_strcmp("cd", node->command[0])))
		ft_cd(node, env);
	else if(!(ft_strcmp("env", node->command[0])))
		ft_env(node, env);
	else if(!(ft_strcmp("exit", node->command[0])))
	{
		ft_exit(node, data);
	}
	else if(!(ft_strcmp("env", node->command[0])))
		ft_env(node, env);
	else if(!(ft_strcmp("export", node->command[0])))
	{
		ft_export(node, data);
	}
	// else if(!(ft_strcmp("unset", node->command[0])))
	// 	ft_unset(node);
	return (g_exit_statuss);
}

int count_char(char *str, char target) {
    int count = 0;
    
	int i = 0;
    while (str[i] != '\0') {
        if (str[i] == target)
		{
            count++;
        }
        i++;
    }
    return (count);
}


// void	add_new_expo(t_export **exp, char *key, char *value) 
// {
// 	t_export *new;

// 	new = new_expo_node(key, value);
// 	ft_lstadd_gr((exp), new);
// }


// t_export	*new_expo_node(char *key, char *value, char *def)
// {
// 	t_export	*new_node;

// 	new_node = malloc(sizeof(t_export));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->key = ft_strdup(key);
// 	new_node->value = ft_strdup(value);
// 	new_node->def = ft_strdup(value);
// 	new_node->next = NULL;
// 	return (new_node);
// }


// void	fill_the_export(t_export **export, t_envies **env)
// {
// 	while((*env) != NULL)
// 	{
// 		(*export)->def = "declare -x ";
// 		(*export)->key = (*env)->key;
// 		(*export)->value = (*env)->value;
// 		(*env) = (*env)->next;
// 	}
// }

int	ft_spl(char	*nodik, t_export **exp, t_envies **env)
{

	(void)nodik;
	(void)exp;
	(void)env;

	// int 	j;
	// int 	i;
	// char 	*key;
	// char	*val;

	// i = 0;
	// j = 0;
	// while(nodik[i])
	// {
	// 	if(nodik[i + 1] && nodik[i] == '=' && nodik[i + 1] == '+')
	// 	{
	// 		key = ft_substr(key, 0, j);
	// 		val = ft_substr((*exp)->value, j + 1, i);
	// 		add_new_expo((exp), key ,val);
	// 		add_new_env((env),key, val);
	// 	}
	// 	else if(nodik[i] == '=')
	// 		j = i;
	// 	i++;
	// }
	// if(j == 0)
	// {
	// 	key = ft_substr(key, 0 ,i);
	// 	add_new_expo((exp), key , NULL);
	// }
	// else
	// {
	// 	key = ft_substr(key, 0, j);
	// 	val = ft_substr(val ,j + 1 , i);
	// 	add_new_expo((exp), key ,val);
	// 	add_new_env((env),key, val);
	// }
	return (0);
}

int ft_env(t_command *node, t_envies *env)
{
	if(!(node->command[1]))
	{
		while(env != NULL)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write (1, "\n", 1);
			env = env->next;
		}
	}
	return (0);
}

