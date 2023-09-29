/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impliment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/29 12:10:46 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_command *node)
{
	if (!(ft_strcmp_up("echo", node->command[0])))
		return (1);
	else if (!(ft_strcmp("pwd", node->command[0])))
		return (1);
	else if (!(ft_strcmp("cd", node->command[0])))
		return (1);
	else if (!(ft_strcmp("env", node->command[0])))
		return (1);
	else if (!(ft_strcmp("exit", node->command[0])))
		return (1);
	else if (!(ft_strcmp("export", node->command[0])))
		return (1);
	else if (!(ft_strcmp("unset", node->command[0])))
		return (1);
	return (0);
}

int	built_in(t_command *node, t_data *data, t_envies *env)
{
	if (!(ft_strcmp_up("echo", node->command[0])))
		ft_echo(data, node);
	else if (!(ft_strcmp("pwd", node->command[0])))
		ft_pwd();
	else if (!(ft_strcmp("cd", node->command[0])))
		ft_cd(node, env, data->export);
	else if (!(ft_strcmp("env", node->command[0])))
		ft_env(node, env);
	else if (!(ft_strcmp("exit", node->command[0])))
		ft_exit(node, data);
	else if (!(ft_strcmp("export", node->command[0])))
		ft_export(node, data);
	else if (!(ft_strcmp("unset", node->command[0])))
		ft_unset(node, env, data->export);
	return (0);
}

int	ft_env(t_command *node, t_envies *env)
{
	if (!(node->command[1]))
	{
		while (env != NULL)
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
