/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:16:59 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/28 19:33:10 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *if_env(char *str, t_envies *env, int exs)
{
	(void)exs;
	int pid;

	pid = getpid();
	if (*str == '\0')
		return ("$");
	if (*str == '$')
		return (ft_itoa(pid));
	if (*str == '?')
		return (ft_itoa(888));
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (env->value);
		env = env->next;
	}
	return ("");
}

void open_fields(t_token *stream, t_envies *env, int exs)
{
	char *name;
	char *dol;
	char *chunk;

	while (stream)
	{
		if (stream->type == WORD || stream->type == EXP_FIELD)
		{
			dol = ft_strchr(stream->value, '$');
			while (dol)
			{
				stream->value = ft_substr(stream->value, 0, ft_strlen(stream->value) - ft_strlen(dol));
				name = env_name(&dol);
				chunk = if_env(name, env, exs);
				stream->value = ft_strjoin(stream->value, chunk);
				stream->value = ft_strjoin(stream->value, dol);
				dol = ft_strchr((stream->value + ft_strlen(stream->value)) - ft_strlen(dol), '$');
			}
		}
		stream = stream->next;
	}
}