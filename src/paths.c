/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:24:39 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 15:49:55 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_path(t_data *data)
{
	t_envies	*first;
	int			i;
	int			len;
	char		**splited;

	first = data->envies;
	while (data->envies)
	{
		if (data->envies->key && !ft_strcmp(data->envies->key, "PATH"))
			break ;
		data->envies = data->envies->next;
	}
	if (!data->envies)
		printf("there is no paths\n");
	splited = ft_split(data->envies->value, ':');
	len = split_len(splited);
	data->paths = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (splited[++i])
		data->paths[i] = ft_strdup(splited[i]);
	data->paths[i] = NULL;
	free_spl(splited);
	data->envies = first;
}
