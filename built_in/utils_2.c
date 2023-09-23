/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:04:20 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 10:26:41 by marihovh         ###   ########.fr       */
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
