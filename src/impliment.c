/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impliment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/16 17:39:48 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_command *node);
int ft_cd(t_command *node);
int ft_pwd(t_command *node);
int ft_unset(t_command *node);
int ft_export(t_command *node);
int ft_env(t_command *node);

int is_built_in(t_command *node)
{
	if(!(ft_strcmp("echo", node->command[0])))
		return (1);
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

int	built_in(t_command *node)
{
	if(!(ft_strcmp("echo", node->command[0])))
	{
		printf("i am echo\n");
		return (1);
	}
	else if(!(ft_strcmp("pwd", node->command[0])))
		ft_pwd(node);
	else if(!(ft_strcmp("cd", node->command[0])))
		ft_cd(node);
	else if(!(ft_strcmp("env", node->command[0])))
		ft_env(node);
	else if(!(ft_strcmp("exit", node->command[0])))
		exit (0);
	else if(!(ft_strcmp("export", node->command[0])))
		ft_export(node);
	else if(!(ft_strcmp("unset", node->command[0])))
		ft_unset(node);
	else
		printf("shyshell: %s: command not found\n", node->command[0]);
	return (0);
}

int ft_echo(t_command *node)
{
	(void)node;
	return (0);
}

int ft_cd(t_command *node)
{
	(void)node;
	return (0);
}

int ft_pwd(t_command *node)
{
	(void)node;
	return (0);
}

int ft_export(t_command *node)
{
	(void)node;
	return (0);
}

int ft_unset(t_command *node)
{
	(void)node;
	return (0);
}

int ft_env(t_command *node)
{
	(void)node;
	return (0);
}

