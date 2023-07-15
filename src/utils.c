/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:46:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/11 15:02:50 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int ft_strcmp(char *str, char *chm)
{
	int i;

	i = -1;
	while (str[++i] || chm[i])
	{
		if (str[i] != chm[i])
			return (1);
	}
	return (0);
}


t_token *new_token(int type, char *str, int op)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = (int)type;
	new_token->value = str;
	new_token->op = op;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

int ft_isspace(int ch)
{
	return (ch == '\t' || ch == ' ');
}

int correct_pipe(char *tmp, char *str)
{
	return (str[0] != '|' && tmp[1] && tmp[1] == ' ');
}

char  *ft_ispipe(char *str)
{
	char *tmp;

	tmp = ft_strchr(str, '|');
	if (!tmp)
		return (0);
	if (correct_pipe(tmp, str))
	{
		printf ("the pipe is right\n");
		return (tmp);
	}
	printf("pipe error\n");
	error_msg("Token error\n");
	return (0);
}

void error_msg(char *str)
{
	printf("%s\n", str);
	exit (1);
}