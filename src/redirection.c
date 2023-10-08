/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:12:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:30:09 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	for_heredoc_helper(void)
{
	error_msg("shyshell: Here-doc error", 1);
	return (-1);
}

int	waiting(int pid, int status, char *filename)
{
	int	ret;

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

int	for_heredoc(char *filename, t_envies *env)
{
	int	pid;
	int	*fds;
	int	status;
	int	ret;

	foo(0);
	status = 0;
	fds = malloc(sizeof(int *) * 2);
	if (pipe(fds) == -1)
		return (for_heredoc_helper());
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		write_here_doc(fds[1], filename, env);
		close(fds[1]);
		free(filename);
		exit(0);
	}
	ret = fds[0];
	if (waiting(pid, status, filename) == -2)
		ret = -2;
	close(fds[1]);
	free(fds);
	return (ret);
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
	char	*name;

	name = NULL;
	while (stream && (stream->type != WORD && stream->type != FIELD \
		&& stream->type != EXP_FIELD))
		stream = stream->next;
	name = no_escape(stream->value);
	return (name);
}
