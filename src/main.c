/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/24 21:40:13 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_hend(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

int signals (void)
{
	struct termios term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSADRAIN, &term_attr);
	signal(SIGINT, signal_hend);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void free_coms(t_command *stream)
{
	t_command *current = stream;
    t_command *nextNode;
	int i;

    while (current != NULL) {
        nextNode = current->next;
		i = -1;
		while (current->command[++i])
			free(current->command[i]);
		free(current->command);
        free(current);
        current = nextNode;
    }
}

void free_tokens(t_token *stream)
{
	t_token *current = stream;
    t_token *nextNode;

    while (current != NULL)
	{
        nextNode = current->next;
		// nextNode->prev = NULL;
        free(current->value);
		free(current);
        current = nextNode;
		// current->prev = NULL;                   
    }
}

void frees(t_data *data)
{
	// int i = -1;
	// free_tokens(data->stream);
	free_coms(data->com_stream);
	// while (data->paths[++i])
	// 	free(data->paths[i]);
	// i = -1;
	// while (data->command[++i])
	// 	free(data->command[i]);	
}

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	(void)environ;
	// t_command *tmp_c;
	t_data *data = NULL;
	char *str;
	
	str = NULL;
	signals();
	data = malloc(sizeof(t_data));
	init_env(&data->envies, environ);
	while (1)
	{
		str = readline("shyshell$ ");
		if (!str)
			exit(0);
		if (str[0])
		{
			add_history(str);
			parse(data, str);
			// if (parse(data, str) == 0)
			// {
				// prin(data->stream, data->com_stream);
				// free_tokens(data->stream);
				// free_env(data->envies);
				// free_coms(data->com_stream);
				// printf("de giteq\n");
				// init_env(&data->envies, environ);
				// prin(data->stream, data->com_stream);
				// free_tokens(data->stream);
				// data->exit_status = execute(data);
				// free_coms(data->com_stream);
				// free_env(data->envies);
				// free_spl(data->paths);
			// }
			// system("leaks minishell");
		}
	}
	// while (1){}
	return (0);
}
