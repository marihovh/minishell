/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/15 16:23:07 by marihovh         ###   ########.fr       */
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
        free(current->value);
		free(current);
        current = nextNode;                   
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
	t_data *data = NULL;
	char *str;
	
	str = NULL;
	signals();
	data = malloc(sizeof(t_data));
	init_env(&data->envies, environ);
	fill_the_export(&data->export, data->envies);
	data->in_c = dup(STDIN);
	data->out_c = dup(STDOUT);
	while (1)
	{
		str = readline("shyshell$ ");
		if (!str)
		{
			printf("exit\n");
			exit(0);
		}
		if (str[0])
		{
			add_history(str);
			if (!parse(data, str))
			{
				free_tokens(data->stream);
				execution(data);
				// system("leaks minishell");
				dup2(data->in_c, 0);
				dup2(data->out_c, 1);
				g_exit_statuss = 0;
				free_coms(data->com_stream);
			}
		}
	}
	return (0);
}


// echon pti writeov lini vor ete echo em anum inch vor file i mej karena gna yte