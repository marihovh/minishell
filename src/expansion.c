/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:16:59 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:21:53 by marihovh         ###   ########.fr       */
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
	char	*ret;	
	char	*tmp;
	char	*value;
	char	*name;

	ret = NULL;
	while (str && str[0])
	{
		if (str[0] != '$')
		{
			dol = ft_strchr(str, '$');
			if (!dol)
			{
				ret = ft_strjoin(ret, str);
				str = NULL;
			}
			else
			{
				tmp = ft_substr(str, 0, ft_strlen(str) - ft_strlen(dol));
				str = ft_strchr(str, '$');
				name = env_name(&str);
				value = if_env(name, env);
				free(name);
				ret = ft_strjoin(ret, tmp);
				free(tmp);
				ret = ft_strjoin(ret, value);
				free(value);
			}
		}
		else
		{
			str = ft_strchr(str, '$');
			name = env_name(&str);
			value = if_env(name, env);
			free(name);
			ret = ft_strjoin(ret, value);
			free(value);
		}
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
					tmp = ft_strdup(stream->value);
					free(stream->value);
					stream->value = open_dol(dol, tmp, env);
					free(tmp);
				}
				stream->type = WORD;
			}
		}
		stream = stream->next;
	}
}
