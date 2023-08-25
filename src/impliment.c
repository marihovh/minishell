/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impliment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/23 16:05:25 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_command *node);
int ft_cd(t_command *node);
int ft_pwd(t_command *node);
int ft_unset(t_command *node, t_envies *env);
int ft_export(t_command *node);
int ft_env(t_command *node, t_envies *env);

int is_built_in(t_command *node)
{
	if(!(ft_strcmp("echo", node->command[0])))
		return (1);
	else if(!(ft_strcmp("pwd", node->command[0])))
		return (1);
	else if(!(ft_strcmp("cd", node->command[0])))
		return (1);
	else if(!(ft_strcmp("env", node->command[0])))
		return (1);
	else if(!(ft_strcmp("exit", node->command[0])))
		return (1);
	else if(!(ft_strcmp("export", node->command[0])))
		return (1);
	else if(!(ft_strcmp("unset", node->command[0])))
		return (1);
	return (0);
}

int	built_in(t_command *node, int *exit_status)
{
	(void)exit_status;
	if(!(ft_strcmp("echo", node->command[0])))
	{
		printf("i am echo\n");
		return (1);
	}
	else if(!(ft_strcmp("pwd", node->command[0])))
		ft_pwd(node);
	else if(!(ft_strcmp("cd", node->command[0])))
		ft_cd(node);
	// else if(!(ft_strcmp("env", node->command[0])))
	// 	// ft_env(node);
	else if(!(ft_strcmp("exit", node->command[0])))
		exit (*exit_status);
	else if(!(ft_strcmp("export", node->command[0]))) 
		ft_export(node);
	// else if(!(ft_strcmp("unset", node->command[0])))
	// 	ft_unset(node);
	return (node->exit_status);
}

int ft_cd(t_command *node)
{
	// const char path[1024];

	// if(getcwd(path, sizeof(path) != NULL))
	// {
	// 	if(chdir(path) == 0)
	// 		printf("\n%s",path);
	// 	perror("chdir() error bro\n");
	// }
	// perror("getcwd() error\n");
	//free
	return (node->exit_status);
}

int ft_echo(t_command *node)
{
	int i = 1;
	if(ft_strcmp("-n",node->command[1]))
	{
		while(node->command[++i])
			printf("%s",node->command[i]);
	}
	printf("\n");
	while(node->command[++i])
		printf("%s",node->command[i]);
	return (node->exit_status);
}


int ft_pwd(t_command *node)
{
	// const char path[1024];

	// if(getcwd(path, sizeof(path) != NULL))
	// 	printf("\n%s",path);
	// perror("getcwd() error\n");
	// //free
	return (node->exit_status);
}

void	ft_lstadd_fr(t_envies **lst, t_envies *new)
{
	if (!lst)
		return ;
	new -> next = *lst;
	*lst = new;
}

void	add_new_el(t_envies **env, char *key, char *value)
{
	t_envies *new;

	new = new_node(key, value);
	ft_lstadd_fr((env), new);
}


//export- mej lcnel envi-i exacy demic declare x

void	fill_the_export(t_export **export, t_envies **env)
{
	(void)export;
	(void)env;
	//printf declare x
}

char	ft_spl(char	*nodik)
{
	int j;
	int i;

	i = 0;
	while(nodik[i])
	{
		if(nodik[i] == '=')
		{
			j = i;
		}
		i++;
	}
	// if(j == 0)
	// 	//exporti mej enq gcum
	// else
	// 	//exporti hamel envi
	return (0);
}



//ete havasar chka gcuma exporti mej
//ete havasarnel ka env-i u export-i mej
//ete havasar ka gcuma erkusi mej kap chuni datarak te liqy

int ft_export(t_command *node)
{
	int i;

	i = 0;
	//ete exporta meank uremn tpi
	while(node->command[++i])
		ft_spl(node->command[i]);
	//add elemenet
	//----if added they can change value by 
	//----give as argument and add+=it will add to the value
	return (0);
}


void	delete_node(t_envies **env, char *del_node)
{
	t_envies *head;
	t_envies *prev;

	head = (*env);
	prev = NULL;
	while(head != NULL)
	{
	if (ft_strcmp(head->key , del_node) == 0)
		{
		if(prev == NULL)
			*(env) = head->next;
		else
			prev->next = head->next;
		free(head);
		free(head->key);
		free(head->value);
		}
	}
	prev = head;
	head = head->next;
}

int ft_unset(t_command *node, t_envies *env)
{
	int			i;
	t_envies	*tmp;

	i = 0;
	tmp = env;
	while(node->command[++i] && env->next)
	{
		if(!(ft_strcmp(node->command[i] , env->key)))
			delete_node(&(env),(env->value));
		env = env->next;	
	}
	env = tmp;
	return (node->exit_status);
}

int ft_env(t_command *node, t_envies *env)
{
	if(!(node->command[1]))
	{
		while(env != NULL)
		{
			printf("%s" , env->key);
			printf("=");
			printf("%s\n" , env->value);
			env = env->next;
		}
	}
	return (node->exit_status);
}

