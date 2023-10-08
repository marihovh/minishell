/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:56:23 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 21:48:32 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_old(t_envies *env, char *path, t_export *export)
{
	char	*new;

	new = find_env(&env, "OLDPWD");
	if (!new || !new[0])
	{
		error_msg("shyshell: cd: OLDPWD not set", 1);
		g_exit_statuss = 1;
		free(new);
		return (1);
	}
	if (!chdir(new))
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		update_pwd(&env, new, path, export);
		free(new);
		return (1);
	}
	free(new);
	return (0);
}

int	cd_old2(t_envies *env, char *path, t_export *export)
{
	char	*new;

	new = find_env(&env, "OLDPWD");
	if (!new || !new[0])
	{
		error_msg("shyshell: cd: OLDPWD not set", 1);
		g_exit_statuss = 1;
		free(new);
		return (1);
	}
	if (!chdir(new))
	{
		update_pwd(&env, new, path, export);
		free(new);
		return (1);
	}
	free(new);
	return (0);
}

int	half_cd_helper(t_envies *env, char *path, t_export *export)
{
	if (cd_old(env, path, export))
		return (1);
	return (0);
}

int	half_cd_helper2(t_envies *env, char *path, t_export *export)
{
	if (cd_old2(env, path, export))
		return (1);
	return (0);
}

int	half_cd(char **command, t_envies *env, char *path, t_export *export)
{
	char	*new;
	int		ret;

	new = NULL;
	ret = 0;
	if (!command[1])
	{
		new = find_env(&env, "HOME");
		if (!chdir(new))
			update_pwd(&env, new, path, export);
		free(new);
		ret = 1;
	}
	else if (command[1][0] == '-' && !command[1][1])
		ret = half_cd_helper(env, path, export);
	else if (command[1][0] == '-' && command[1][1] == '-')
		ret = half_cd_helper2(env, path, export);
	else if (command[1][0] == '-')
	{
		error_msg("cd: usage: cd [dir]", 1);
		g_exit_statuss = 1;
		ret = 1;
	}
	return (ret);
}
