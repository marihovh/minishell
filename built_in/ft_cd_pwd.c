/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:56:23 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 10:19:17 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_env(t_envies **env, char *key)
{
	while (*env)
	{
		if (!ft_strcmp((*env)->key, key))
			return (ft_strdup((*env)->value));
		env = &(*env)->next;
	}
	return (0);
}

void	update_pwd(t_envies **env, char *new, char *old)
{
	while (*env)
	{
		if (!ft_strcmp((*env)->key, "OLDPWD"))
		{
			if ((*env)->value)
				free((*env)->value);
			(*env)->value = ft_strdup(old);
		}
		if (!ft_strcmp((*env)->key, "PWD"))
		{
			free((*env)->value);
			(*env)->value = ft_strdup(new);
		}
		env = &(*env)->next;
	}
}

int	half_cd(char **command, t_envies *env, char *path)
{
	char	*new;

	new = NULL;
	if (!command[1])
	{
		new = find_env(&env, "HOME");
		if (!chdir(new))
			update_pwd(&env, new, path);
	}
	else if (command[1][0] == '-' && !command[1][1])
	{
		new = find_env(&env, "OLDPWD");
		if (!new[0])
			error_msg("shyshell: cd: OLDPWD not set", 1);
		if (!chdir(new))
			update_pwd(&env, new, path);
	}
	else if (command[1][0] == '-')
	{
		error_msg("cd: usage: cd [dir]", 1);
		g_exit_statuss = 1;
	}
	free(new);
	return (0);
}

int	ft_cd(t_command *node, t_envies *env)
{
	char	path[1024];
	char	*new;

	new = NULL;
	getcwd(path, sizeof(path));
	half_cd(node->command, env, path);
	if (node->command[1])
	{
		new = ft_strdup(node->command[1]);
		if (!chdir(new))
			update_pwd(&env, new, path);
		else
		{
			write(2, "shyshell: ", 10);
			write(2, node->command[1], ft_strlen(node->command[1]));
			write(2, ": No such file or directory\n", 28);
			g_exit_statuss = 1;
			free(new);
			return (0);
		}
	}
	free(new);
	g_exit_statuss = 0;
	return (0);
}

int	ft_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	g_exit_statuss = 0;
	return (0);
}
