/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 14:00:51 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_shlvl(t_envies **env)
{
	int	num;

	while (*env)
	{
		if (!ft_strcmp("SHLVL", (*env)->key))
		{
			num = ft_atoi((*env)->value);
			num += 1;
			free((*env)->value);
			(*env)->value = ft_itoa(num);
		}
		env = &(*env)->next;
	}
}

void	init1(t_data *data, char **environ)
{
	init_env(&data->envies, environ);
	update_shlvl(&data->envies);
	fill_the_export(&data->export, data->envies);
	data->home = find_env(&data->envies, "HOME");
	data->in_c = dup(STDIN);
	data->out_c = dup(STDOUT);
	signals();
}

void	parse_and_exec(t_data *data, char *str)
{
	t_token	*tmp;

	add_history(str);
	if (!parse(data, str))
	{
		tmp = NULL;
		tmp = data->stream;
		to_struct(data, &data->com_stream);
		data->stream = tmp;
		execution(data);
		free_tokens(data->stream);
		free_coms(data->com_stream);
	}
	dup2(data->in_c, 0);
	dup2(data->out_c, 1);
}

int	main(int argc, char **argv, char **environ)
{
	t_data	*data;
	char	*str;

	if (argc > 1 && argv[0])
		printf("are you kidding? 😒\n");
	data = malloc(sizeof(t_data));
	init1(data, environ);
	while (1)
	{
		str = readline("shyshell$ ");
		if (!str)
		{
			printf("exit\n");
			exit(0);
		}
		if (str[0])
			parse_and_exec(data, str);
		else
			free(str);
	}
	return (0);
}
