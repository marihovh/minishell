/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:12:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 14:12:33 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//erkushabti 11

void write_here_doc(int fd, char *filename)
{
	char *line;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	while(1)
	{
		line = readline("> ");
		if ((line == NULL || ft_strcmp(line, filename) == 0))
			break ;
		write(fd , line, ft_strlen(line));
		write(fd , "\n", 1);
	}
	close(fd);
}

int	for_heredoc(char *filename)
{
	int pid;
	int fds[2];
	int status;

	foo(0);
	if (pipe(fds) == -1)
	{
		error_msg("shyshell: Here-doc error", 1);
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		write_here_doc(fds[1], filename);
		close(fds[1]);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)) 
	{
		if (WTERMSIG((status)) == SIGINT)
			write(1, "\n", 1);
		fds[0] = -2;
	}
	foo(1);
	close(fds[1]);
	return (fds[0]);
}
// here-doc signal error

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
	new[j] = '\0';
	return (new);
}

char *file_name(t_token *stream)
{
	char *name;

	while (stream && stream->type != WORD)
		stream = stream->next;
	name = no_escape(stream->value);
	if (!(stream))
		return (NULL);
	return (name);
}

void find_com_2(t_token **stream, t_token *tmp, t_token *com)
{
	t_token *ww;
	t_token *aa;
	
	aa = (*stream);
	while ((*stream) && (*stream) != tmp->next)
	{
		ww = (*stream)->next;
		free((*stream)->value);
		free(*stream);
		(*stream) = ww;
	}
	aa = aa->prev;
    while (aa && aa != com)
	{
		ww = aa->prev;
        free(aa->value);
		free(aa);
        aa = ww;                   
    }
	(*stream) = com;
}

void set_fd(t_token **stream, int fd, int fedo)
{
	if (!(*stream))
		return ;
	if (fedo == 1)
		(*stream)->in = fd;
	else
		(*stream)->out = fd;
}

void soo_word(t_token **tmp)
{
	while (*tmp && (*tmp)->type != WORD)
		(*tmp) = (*tmp)->next;
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
	soo_word(&tmp);
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
	find_com_2(stream, tmp, com);
	set_fd(stream, fd, fedo);
}
