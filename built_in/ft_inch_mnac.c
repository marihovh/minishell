/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inch_mnac.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:46:41 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:53:13 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_char(char ch)
{
	return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_');
}

int	other_char(char ch)
{
	return (first_char(ch) || (ch >= '0' && ch <= '9'));
}

void	exp_error(char *what, char *key)
{
	ft_putstr_fd("shyshell : ", 2);
	ft_putstr_fd(what, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

int	ft_unset(t_command *node, t_envies *env, t_export *export)
{
	int		i;
	char	*key;

	i = 1;
	while (node->command[i])
	{
		key = valid_key(node->command[i], NULL, "unset");
		if (!key)
			return (1);
		env_delete(&env, node->command[i]);
		export_delete(&export, node->command[i]);
		i++;
	}
	return (g_exit_statuss);
}

void	update_pwd(t_envies **env, char *new, char *old, t_export *export)
{
	int	flag;

	flag = 0;
	while (*env)
	{
		if (!ft_strcmp((*env)->key, "OLDPWD"))
		{
			flag = 1;
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
	if (flag == 0)
		(*env) = new_node("OLDPWD", old);
	update_exp_value(&export, "OLDPWD", old);
	update_exp_value(&export, "PWD", new);
}
