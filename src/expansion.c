/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:16:59 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 10:58:45 by marihovh         ###   ########.fr       */
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

char	*open_dol(char *dol, char *str, t_envies *env)
{
	char	*name;
	char	*value;
	char	*ret;

	while (dol)
	{
		str = ft_substr(str, 0, ft_strlen(str) - ft_strlen(dol));
		name = env_name(&dol);
		value = if_env(name, env);
		free(name);
		ret = ft_strjoin(str, value);
		free(value);
		ret = ft_strjoin(ret, dol);
		dol = ft_strchr((str + ft_strlen(str)) - ft_strlen(dol), '$');
	}
	return (ret);
}

void	open_fields(t_token *stream, t_envies *env)
{
	char	*dol;
	char	*tmp;

	while (stream)
	{
		if (stream->type == WORD || stream->type == EXP_FIELD)
		{
			if (will_open(stream))
			{
				dol = ft_strchr(stream->value, '$');
				if (dol)
				{
					tmp = open_dol(dol, stream->value, env);
					free(stream->value);
					stream->value = ft_strdup(tmp);
					free(tmp);
				}
			}
			stream->type = WORD;
		}
		if (stream->type == FIELD)
			stream->type = WORD;
		stream = stream->next;
	}
}
