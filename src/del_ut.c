#include "../minishell.h"

void prin(t_token *stream, t_command *com_stream)
{
	int i = -1;
	while (stream)
	{
		printf("stream:%s\n", stream->value);
		stream = stream->next;
	}
	printf("\n-----------------------------------------\n");
	while (com_stream)
	{
		printf("command:");
		i = -1;
		while (com_stream->command[++i])
			printf("%s ", com_stream->command[i]);
		printf("\n");
		com_stream = com_stream->next;
	}
}


void pri(t_command *com_stream)
{
	while (com_stream)
	{
		printf("command:%s\n", com_stream->command[0]);
		printf("in:%i   out:%i\n", com_stream->in, com_stream->out);
		com_stream = com_stream->next;
	}
}
void print_en(t_envies *envies)
{
	while (envies)
	{
		printf("%s=%s\n", envies->key, envies->value);
		envies = envies->next;
	}
}