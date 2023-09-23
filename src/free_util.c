/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:41:24 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 11:31:46 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_export(t_export *export)
{
	t_export	*current;
	t_export	*next_node;

	if (!export)
		return ;
	current = export;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->value);
		free(current->key);
		free(current);
		current = next_node;
	}
}

void	free_env(t_envies *env)
{
	t_envies	*current;
	t_envies	*next_node;

	if (!env)
		return ;
	current = env;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->value);
		free(current->key);
		free(current);
		current = next_node;
	}
}

int	ft_lstcnt(t_envies *lst)
{
	t_envies	*curr;
	int			cnt;

	curr = lst;
	cnt = 0;
	while (curr != NULL)
	{
		curr = curr -> next;
		cnt++;
	}
	return (cnt);
}

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

int	ft_pip_cnt(t_data *data)
{
	t_command	*tmp;
	int			i;

	tmp = data->com_stream;
	i = 0;
	while (data->com_stream)
	{
		data->com_stream = data->com_stream->next;
		i++;
	}
	data->com_stream = tmp;
	return (i - 1);
}
