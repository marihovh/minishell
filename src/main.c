/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/09 20:20:03 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_hend(int signum)
{
	if (signum == SIGINT)
	{
		printf("ctrl+c\n");
		exit (1);
	}
}

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	t_data *data = NULL;
	
	init_line(data, environ); 
	return (0);
}
