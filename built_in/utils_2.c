/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:04:20 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/07 12:19:28 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printing_export(t_data *data)
{
	while(data->export)
	{
		printf("%s",data->export->def);
		printf("%s",data->export->key);
		printf("%s\n",data->export->value);
		data->export = data->export->next;
	}
}

void	add_new_env(t_envies **env, char *key, char *value)
{
	t_envies *new;

	new = new_node(key, value);
	ft_lstadd_fr((env), new);
}

int isWordBoundary(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

int count_matches(char *str, char *substr)
{
    int i = 0, j, count = 0;

    while (str[i]) {
        j = 0;
        while (substr[j] && str[i + j] == substr[j]) {
            j++;
        }
        if (!substr[j] && (i == 0 || isWordBoundary(str[i - 1])) &&
            (str[i + j] == '\0' || isWordBoundary(str[i + j])))
        {
            count++;
        }
        i++;
    }
    return count;
}

int ft_strcmp_up(char *str, char *chm)
{
    int i;

    i = -1;
    while (str[++i] || chm[i])
    {
        if (tolower(str[i]) != tolower(chm[i]))
            return (1);
    }
    return (0);
}