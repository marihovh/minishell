/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:46:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 08:45:38 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_strcmp(char *str, char *chm)
{
	int	i;

	i = -1;
	while (str[++i] || chm[i])
	{
		if (str[i] != chm[i])
			return (1);
	}
	return (0);
}

t_token	*new_token(int type, char *str, int op)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = (int)type;
	new_token->value = ft_strdup(str);
	free(str);
	new_token->op = op;
	new_token->in = STDIN;
	new_token->out = STDOUT;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

int	correct_pipe(char *tmp, char *str)
{
	return (str[0] != '|' && tmp[1] && tmp[1] == ' ');
}

char	*ft_ispipe(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '|');
	if (!tmp)
		return (0);
	if (correct_pipe(tmp, str))
		return (tmp);
	error_msg("shyshell: |: pipe error", 1);
	return (0);
}

void	error_msg(char *str, int exs)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	g_exit_statuss = exs;
}
