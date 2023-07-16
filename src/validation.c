/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:47:33 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/16 10:09:09 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void validation(t_token *stream)
{
	while (stream)
	{
		if (stream->type == PIPE)
		{
			if (!stream->next)
				printf("hyre-doc\n");
			if (stream->next->type != SP || stream->prev->type != SP)
			{
				printf("this is error axpers\n");
				exit (1);
			}
		}
		stream = stream->next;
	}
}