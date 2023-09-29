/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:16:59 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/28 22:24:35 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*if_env(char *str, t_envies *env)
{
	int	pid;

	pid = getpid();
	if (*str == '\0')
		return (ft_strdup("$"));
	if (*str == '/')
		return (ft_strdup("$/"));
	if (*str == '$')
		return (ft_strdup(""));
	if (*str == '?')
		return (ft_itoa(g_exit_statuss));
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

int	will_open(t_token *stream)
{
	if (stream->prev && stream->prev->type == REDIR_SO)
		return (0);
	else if (stream->prev && stream->prev->prev \
		&& stream->prev->prev->type == REDIR_SO)
		return (0);
	return (1);
}

void open_fields(t_token *stream, t_envies *env)
{
	char *name;
	char *dol;
	char *chunk;
	char *tmp;
	
	while (stream)
	{
		if (stream->type == WORD || stream->type == EXP_FIELD)
		{
			dol = ft_strchr(stream->value, '$');
			while (dol)
			{
				tmp = ft_strdup(stream->value);
				free(stream->value);
				stream->value = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(dol));
				free(tmp);
				name = env_name(&dol);
				chunk = if_env(name, env);
				free(name);
				stream->value = ft_strjoin(stream->value, chunk);
				free(chunk);
				stream->value = ft_strjoin(stream->value, dol);
				dol = ft_strchr((stream->value + ft_strlen(stream->value)) - ft_strlen(dol), '$');
			}
		}
		stream = stream->next;
	}
}
