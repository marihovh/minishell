/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:13:03 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/09 01:18:13 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_name(char *filename)
{
	int	nb;

	nb = not_file(filename);
	if (nb == 3)
		free(filename);
	return (nb);
}

void	under_(t_data *data)
{
	int	i;

	i = 0;
	while (data->com_stream->command[i])
		i++;
	update_env_value(&data->envies, "_", data->com_stream->command[i - 1]);
}

int	execution(t_data *data)
{
	data->pip_cnt = ft_pip_cnt(&data->com_stream);
	if (!data->pip_cnt)
		one_com(data);
	else
	{
		piping(data);
		dup2(data->in_c, 0);
		dup2(data->out_c, 1);
	}
	return (0);
}

void	find_com_2(t_token **stream, t_token *tmp, t_token *com)
{
	t_token	*ww;
	t_token	*aa;

	aa = (*stream);
	if (aa && aa->prev)
	{
		aa = aa->prev;
		while (aa && aa != com)
		{
			ww = aa->prev;
			free(aa->value);
			free(aa);
			aa = ww;
		}
	}
	while ((*stream) && (*stream) != tmp->next)
	{
		ww = (*stream)->next;
		free((*stream)->value);
		free(*stream);
		(*stream) = ww;
	}
}

int	valid_helper(void)
{
	g_exit_statuss = 0;
	return (1);
}
