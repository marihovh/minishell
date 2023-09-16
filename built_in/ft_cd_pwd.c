/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:56:23 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/15 14:27:29 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(t_command *node,  t_envies *env)
{
	char	path[1024];
	int 	i;

	i = 0; 
	if(!node->command[++i])
	{
		while(env)
		{
			if(!(ft_strcmp(env->key, "HOME")))
			{
				printf("%s\n", env->value);
				break;
			}
		env = env->next;
		}
		return (0);
	}
	if (getcwd(path, sizeof(path) ) != NULL)
	{
		if(chdir(path) == 0)
		{
			if(!(ft_strcmp(node->command[i],"..")))
			{
				if(chdir("..") != 0)
					perror("error\n");
				printf("%s\n",getcwd(path, sizeof(path))); 
			}
			else if (!(ft_strcmp(node->command[i], "//")))
			{
				if(chdir("//") != 0)
					perror("error\n");
				printf("%s\n",getcwd(path, sizeof(path))); 
			}
			else if(!(ft_strcmp(node->command[i],"Desktop")))
			{
				if(chdir("Desktop") != 0)
					perror("error\n");
				printf("%s\n",getcwd(path, sizeof(path))); 
			}
			else
			{
				if(chdir(node->command[i]) != 0)
					perror("error\n");
				else
					printf("%s\n",getcwd(path, sizeof(path))); 
			}
		}
	}
	return (g_exit_statuss);
}

int ft_pwd(t_command *node)
{
	(void)node;
	char path[1024];

	if(getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	return (g_exit_statuss);
}
