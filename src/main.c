/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/21 21:19:37 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void signal_hend(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		// write(STDIN_FILENO, "\n\n", 2);
	}
	return ;
}

void sig_hend(int num)
{
	(void)num;
	// ft_exit();
	exit(0);
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

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	t_data *data = NULL;
	char *str;
	
	str = NULL;
	signals();
	data = malloc(sizeof(t_data));
	init_line(data, environ); 
	return (0);
}


// int main(int argc, char **argv, char **environ)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_data *data = NULL;
// 	char *str;

// 	str = NULL;
// 	(void)environ;
// 	data = malloc(sizeof(t_data));
// 	while(1)
// 	{
// 		signals();
// 		str = readline("shyshell$ ");
// 		if (!str)
// 		{
// 			write(1, "\n", 1);
// 			exit(0);
// 		}
// 		if (!str[0])
// 			continue;
// 		else
// 		{
// 			init_env(&data->envies, environ);
// 			add_history(str);
// 			if (parse(data, str) == 0)
// 				execute(data);
// 			printf("exit_stat:%i\n", data->exit_status);
// 			data->exit_status = 0;
// 		}
// 	}
// 	return (0);
// }