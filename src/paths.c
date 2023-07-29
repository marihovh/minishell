/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:24:39 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/27 17:34:58 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_path(t_data *data)
{
	int i;
	char **splited;
	while (data->envies)
	{
		if (data->envies->key && !ft_strncmp(data->envies->key, "PATH", 4))
			break ;
		data->envies = data->envies->next;
	}
	if (!data->envies)
		printf("there is no paths\n");
	splited = ft_split(data->envies->value, ':');
	i = -1;
	while (splited[++i])
		data->paths[i] = splited[i];
}