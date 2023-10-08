/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:04:20 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 21:48:35 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printing_export(t_export *export)
{
	while (export)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(export->key, 1);
		if (export->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(export->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		export = export->next;
	}
}

int	ft_strcmp_up(char *str, char *chm)
{
	int	i;

	i = -1;
	while (str[++i] || chm[i])
		if (tolower(str[i]) != tolower(chm[i]))
			return (1);
	return (0);
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

int	ft_cd(t_command *node, t_envies *env, t_export *export)
{
	char	path[1024];
	char	*new;

	new = NULL;
	g_exit_statuss = 0;
	getcwd(path, sizeof(path));
	if (!half_cd(node->command, env, path, export))
	{
		if (node->command[1])
		{
			new = ft_strdup(node->command[1]);
			if (!chdir(new))
				update_pwd(&env, new, path, export);
			else
			{
				ft_putstr_fd("shyshell: ", 2);
				ft_putstr_fd(node->command[1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_exit_statuss = 1;
			}
		}
	}
	free(new);
	return (0);
}
