/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impliment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/11 17:38:43 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_command *node);
int ft_cd(t_command *node);
int ft_pwd(t_command *node);
int ft_unset(t_command *node);
int ft_export(t_command *node);
int ft_env(t_command *node);
int ft_exit(t_command *node);




int	built_one(t_command *node)
{
	int i;

	i = 0;
	while(node->command[i])
	{
		printf(":%s:\n" , node->command[i]);
		if(!(ft_strncmp("echo", node->command[i]), 5))
			ft_echo(node);
		if(!(ft_strncmp("pwd", node->command[i]), 4))
			ft_pwd(node);
		if(!(ft_strncmp("cd", node->command[i]), 3))
			ft_cd(node);
		if(!(ft_strncmp("env", node->command[i]), 4))
			ft_env(node);
		if(!(ft_strncmp("exit", node->command[i]), 5))
			ft_exit(node);
		if(!(ft_strncmp("export", node->command[i]), 7))
			ft_export(node);
		if(!(ft_strncmp("unset", node->command[i]), 6))
			ft_unset(node);
		i++;
	}
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

int ft_exit(t_command *node)
{
	(void)node;
	return (0);
}
