/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impliment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:19:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/30 15:33:14 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_command *node);
int ft_cd(t_command *node);
int ft_pwd(t_command *node);
int ft_unset(t_command *node, t_envies *env);
int ft_export(t_command *node, t_export **exp, t_envies **env);
int ft_env(t_command *node, t_envies *env);

void	delete_node(t_envies **env, char *del_node);
void	add_new_env(t_envies **env, char *key, char *value);
void	add_new_expo(t_export **exp, char *key, char *value);
void	fill_the_export(t_export **export, t_envies **env);
t_export	*new_expo_node(char *key, char *value);
int	ft_spl(char	*nodik, t_export **exp, t_envies **env);
void	ft_lstadd_fr(t_envies **lst, t_envies *new);
void	ft_lstadd_gr(t_export **lst, t_export *new);


int ft_strcmp_up(char *str, char *chm)
{
    int i;

    i = -1;
    while (str[++i] || chm[i])
    {
        if (tolower(str[i]) != tolower(chm[i]))
            return (1);
    }
    return (0);
}

int is_built_in(t_command *node)
{
	if(!(ft_strcmp_up("echo", node->command[0])))
	{
		return (1);
	}
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


int	built_in(t_command *node, t_data *data)
{
	// (void)exit_status;
	if(!(ft_strcmp_up("echo", node->command[0])))
	{
		ft_echo(node);
		return (1);
	}
	else if(!(ft_strcmp("pwd", node->command[0])))
		ft_pwd(node);
	else if(!(ft_strcmp("cd", node->command[0])))
		ft_cd(node);
	// else if(!(ft_strcmp("env", node->command[0])))
	// 	// ft_env(node);
	else if(!(ft_strcmp("exit", node->command[0])))
		exit (0);
	else if(!(ft_strcmp("export", node->command[0]))) 
		ft_export(node, &(data)->export, (&(data)->envies));
	// else if(!(ft_strcmp("unset", node->command[0])))
	// 	ft_unset(node);
	return (node->exit_status);
}

//envien - homey 
int ft_cd(t_command *node)
{
	char	path[1024];
	int 	i;

	i = 0;
	// (void)env;
	if(!node->command[++i])
		printf("/user/liaydiny");
		//gnal/user/liaydiny home
	//ete / sksel 0-ic
	//erb $ loop envineri vrayov
	if(getcwd(path, sizeof(path) )!= NULL)
	{
		printf("%s\n",path);
		if(chdir(path) == 0)
		{

				if(!(ft_strcmp(node->command[i],"..")))
					{
						chdir("..");
						printf("%s\n",getcwd(path, sizeof(path))); 
					}
				else if ( !(ft_strcmp(node->command[i], "//")))
				{
					chdir("//");
					printf("%s\n",getcwd(path, sizeof(path))); 
				}
				else
				{
					chdir(node->command[i]);
					if(getcwd(path, sizeof(path) )!= NULL)
						printf("%s\n",path);
				}
		}
	}
	return (node->exit_status);
}

//ete mekic shata tpel
// ete mi hata okay
// ete meki mej shat ka et antesum a ete ka mi argument vory parunakuma -n mi hat fsyo newline 



int isWordBoundary(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

int count_matches(char *str, char *substr)
{
    int i = 0, j, count = 0;

    while (str[i]) {
        j = 0;
        while (substr[j] && str[i + j] == substr[j]) {
            j++;
        }
        if (!substr[j] && (i == 0 || isWordBoundary(str[i - 1])) &&
            (str[i + j] == '\0' || isWordBoundary(str[i + j])))
        {
            count++;
        }
        i++;
    }
    return count;
}


int ft_echo(t_command *node)
{
	int i;
	int j;
	int sharunakeli = 0;
	if(!(node->command[1]))
		printf("\n");
	j = 0;
	i = 1;
	while(node->command[i] && node->command[i][0] == '-')
	{
		if(!(node->command[i][0] == '-'))
		{
			sharunakeli = i;
			break;
		}
		j = 1;
		while(node->command[i][j])
		{
			if(!(node->command[i][j] == 'n'))
				break;
			j++;
		}
		i++;
	}
	i = 0;
	if(sharunakeli == 0)
	{
		while(node->command[++i])
		{
			printf("%s",node->command[i]);
			if(node->command[i + 1])
				printf(" ");
		}
	}
	else
	{
		while(node->command[++sharunakeli])
		{
			printf("%s",node->command[sharunakeli]);
			if(node->command[sharunakeli + 1])
				printf(" ");
		}
	}
	return (node->exit_status);
}


int ft_pwd(t_command *node)
{
	char path[1024];

	
	if(getcwd(path, sizeof(path)) != NULL)
		printf("%s\n",path);
	return (node->exit_status);
}

void	ft_lstadd_fr(t_envies **lst, t_envies *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_gr(t_export **lst, t_export *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}


void	add_new_expo(t_export **exp, char *key, char *value)
{
	t_export *new;

	new = new_expo_node(key, value);
	ft_lstadd_gr((exp), new);
}

void	add_new_env(t_envies **env, char *key, char *value)
{
	t_envies *new;

	new = new_node(key, value);
	ft_lstadd_fr((env), new);
}



t_export	*new_expo_node(char *key, char *value)
{
	t_export	*new_node;

	new_node = malloc(sizeof(t_export));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value =ft_strdup(value);
	new_node->def = "declare -x ";
	//kam malloc
	new_node->next = NULL;
	return (new_node);
}


void	fill_the_export(t_export **export, t_envies **env)
{
	while((*env) != NULL)
	{
		(*export)->def = "declare -x ";
		(*export)->key = (*env)->key;
		(*export)->value = (*env)->value;
		(*env) = (*env)->next;
	}
}

int	ft_spl(char	*nodik, t_export **exp, t_envies **env)
{
	int 	j;
	int 	i;
	char 	*key;
	char	*val;

	i = 0;
	j = 0;
	while(nodik[i])
	{
		if(nodik[i + 1] && nodik[i] == '=' && nodik[i + 1] == '+')
		{
			key = ft_substr(key, 0, j);
			val = ft_substr((*exp)->value, j + 1, i);
			add_new_expo((exp), key ,val);
			add_new_env((env),key, val);
		}
		else if(nodik[i] == '=')
			j = i;
		i++;
	}
	if(j == 0)
	{
		key = ft_substr(key, 0 ,i);
		add_new_expo((exp), key , NULL);
	}
	else
	{
		key = ft_substr(key, 0, j);
		val = ft_substr(val ,j + 1 , i);
		add_new_expo((exp), key ,val);
		add_new_env((env),key, val);
	}
	return (0);
}

int ft_export(t_command *node, t_export **exp, t_envies **env)
{
	int i;

	i = 0;
	fill_the_export(&(*exp), &(*env));
	while(node->command[++i])
		ft_spl(node->command[i], &(*exp), &(*env));
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

