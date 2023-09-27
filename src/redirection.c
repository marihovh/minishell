/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:12:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/24 03:57:39 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	for_heredoc_helper(void)
{
	error_msg("shyshell: Here-doc error", 1);
	return (-1);
}

int waiting (int pid, int status, char *filename)
{
	int ret;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG((status)) == SIGINT)
			write(1, "\n", 1);
		free(filename);
		ret = -2;
	}
	foo(1);
	return (0);
}

int	for_heredoc(char *filename)
{
	int	pid;
	int	fds[2];
	int	status;

	foo(0);
	status = 0;
	if (pipe(fds) == -1)
		return (for_heredoc_helper());
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		write_here_doc(fds[1], filename);
		free(filename);
		close(fds[1]);
		exit(0);
	}
	if (waiting(pid, status, filename) == -2)
		fds[0] = -2;
	close(fds[1]);
	return (fds[0]);
}

char	*no_escape(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == 92)
			i++;
		new[j++] = str[i];
	}
	new[j] = '\0';
	return (new);
}

char	*file_name(t_token *stream)
{
	char	*name = NULL;

	while (stream && (stream->type != WORD && stream->type != FIELD \
		&& stream->type != EXP_FIELD))
		stream = stream->next;
	name = no_escape(stream->value);
	return (name);
}

void	find_com_2(t_token **stream, t_token *tmp, t_token *com)
{
	t_token	*ww;
	t_token	*aa;

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
