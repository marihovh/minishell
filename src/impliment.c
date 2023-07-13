/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impliment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/11 17:38:43 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_data *data, t_token *token)
{
	if (!token->next || !token->next->next)
	{
		// printf("OK echo\n");
		data->exit_status = 0;
		return ;
	}
	token = token->next->next;
	if (token->type == WORD && !ft_strcmp(token->value, "-n"))
	{
		printf("echo with option\n");
		if (!token->next || !token->next->next)
		{
			data->exit_status = 0;
			return ; 
		}
		token = token->next->next;
	}
	if (token->type == FIELD)
		printf("echo with field\n");
	else if (token->type == EXP_FIELD)
		printf("echo with exp_field\n");
}

void ft_cd(t_data *data, t_token *token)
{
	(void)data;
	(void)token;
}

void ft_pwd(t_data *data, t_token *token)
{
	printf("%s\n", getenv("PWD"));
	(void)data;
	(void)token;
}
