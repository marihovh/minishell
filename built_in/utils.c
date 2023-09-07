/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:58:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/07 12:03:33 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_fr(t_envies **lst, t_envies *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_gr(t_export **lst, t_export *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}
char	*f_k(char	*str)
{
	char	*key;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while(str[++i])
	{
		if(str[i] == '=')
			break;
	}
	if(i == 0)
		perror("erron\n");
	key = malloc(sizeof(char) * i + 1);
	if(!key)
		return (NULL);
	while(++j < i)
		key[j] = str[j];
	return (key);
}

char	*f_v(char	*str)
{
	char	*value;
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	while(str[++i])
	{
		if(str[i] == '=')
			break;
	}
	j = i;
	while(str[i])
		i++;
	value = malloc(sizeof(char) * i - j + 1);
	if(!value)
		return (NULL);
	while(j < i)
	{
		value[k] = str[j];
		k++;
		j++;
	}
	return(value);
}