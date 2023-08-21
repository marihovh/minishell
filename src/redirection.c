/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:12:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/18 20:02:11 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int init_and_check_fd(int fd)
{
	if (fd == -1)
	{
		printf("that file doesn't exist\n");
		return (1);
	}
	return(0);
}

void	for_heredoc(char *filename, int fd)
{
	char *line;

	filename += 4;
	line = readline("> ");
	while(line && ft_strcmp(line, filename)) // chgitem vocn signal dnenq vor ete signal ekav eli gre u durs ga
	{
		write(fd , line, ft_strlen(line));
		write(fd , "\n", 1);
		line = readline("> ");
	}
}

char *file_name(t_token *stream)
{
	while (stream && stream->type != WORD)
		stream = stream->next;
	if (!(stream))
		return (NULL);
	return (stream->value);
}

// void find_com(t_token **stream, int fd , int fedo)
// {
// 	if (!(*stream)->prev)
// 		return ;
// 	while (*stream && (*stream)->type != WORD)
// 		stream = &(*stream)->prev;
// 	if (!(stream))
// 		return ;
// 	printf("ss:%s\n", (*stream)->value);
// 	if (fedo == 1)
// 		(*stream)->in = fd;
// 	else
// 		(*stream)->out = fd;
// }

void find_com(t_token **stream, int fd , int fedo)
{
	(void)fd;
	(void)fedo;
	t_token *com;
	t_token *tmp;

	com = (*stream);
	tmp = (*stream);
	if ((com)->prev)
		while (com && com->type != WORD)
			com = com->prev;
	while (tmp && tmp->type != WORD)
		tmp = tmp->next;
	if (com != (*stream))
		com->next = tmp->next;
	else
	{
		com = NULL;
		(*stream) = com;
		return ;
	}
	// com->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = com;
	else 
		com->next = NULL;
	(*stream) = com;
	if (!(*stream))
		return ;
	if (fedo == 1)
		(*stream)->in = fd;
	else
		(*stream)->out = fd;
}
