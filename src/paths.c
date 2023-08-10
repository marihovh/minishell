/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:24:39 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/10 13:45:00 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_path(t_data *data)
{
	t_envies *first;
	int i;
	char **splited;

	first = data->envies; 
	while (data->envies)
	{
		if (data->envies->key && !ft_strncmp(data->envies->key, "PATH", 4))
			break ;
		data->envies = data->envies->next;
	}
	if (!data->envies)
		printf("there is no paths\n");
	splited = ft_split(data->envies->value, ':');
	//stexic e segfauklty
	int len;

	len = len_spl(splited);
	data->paths = malloc
	i = -1;
	while (splited[++i])
		data->paths[i] = splited[i];
	data->envies = first;
}
