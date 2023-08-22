/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:12:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/22 14:58:10 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int init_and_check_fd(int fd, char *filename)
{
	if (fd == -1)
	{
		printf("shyshell: %s: No such file or directory\n", filename);
		return (1);
	}
	return(0);
}

void write_here_doc(int fd, char *filename)
{
	char *line;
	
	line = readline("> ");
	while(line && ft_strcmp(line, filename))
	{
		write(fd , line, ft_strlen(line));
		write(fd , "\n", 1);
		line = readline("> ");
	}
	close(fd);
}

int	for_heredoc(char *filename)
{
	int pid;
	int fds[2];

	if (pipe(fds) == -1)
	{
		printf("here-doc error\n");
		return (-1);
	}	
	pid = fork();
	if (pid == 0)
	{
		signals();
		close(fds[0]);
		write_here_doc(fds[1], filename);
		exit(0);
	}
	else
	{
		close (fds[1]);
		waitpid(pid, NULL, 0);
		return (fds[0]);
	}
}

char *no_escape(char *str)
{
	char *new;
	int i;
	int j;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(str));
	while (str[++i])
	{
		if (str[i] == 92)
			i++;
		new[j++] = str[i];
	}
	return (new);
}

char *file_name(t_token *stream)
{
	while (stream && stream->type != WORD)
		stream = stream->next;
	stream->value = no_escape(stream->value);
	if (!(stream))
		return (NULL);
	return (stream->value);
}

void find_com(t_token **stream, int fd , int fedo)
{
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
