/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:04:20 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/13 20:14:33 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printing_export(t_export *export)
{
	while(export)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(export->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(export->value, 1);
		ft_putstr_fd("\"\n", 1);
		
		export = export->next;
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