/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepforexecute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:35:21 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/17 22:17:25 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**alloc_and_copy(char **arr, int len)
{
	char	**new_arr;
	int		i;

	i = 0;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			while (--i >= 0)
				free(new_arr[i]);
			free(new_arr);
			return (NULL);
		}
		i++;
	}
	return (new_arr);
}

char	**add_token(char **arr, char *token)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	i = 0;
	while (arr && arr[len])
		len++;
	new_arr = alloc_and_copy(arr, len);
	if (!new_arr)
		return (NULL);
	new_arr[len] = ft_strdup(token);
	if (!new_arr[len])
	{
		while (--i >= 0)
			free(new_arr[i]);
		free(new_arr);
		return (NULL);
	}
	new_arr[len + 1] = NULL;
	free_2d_array(arr);
	return (new_arr);
}

t_loads	*create_node(char **cmd, char **redir, int type)
{
	t_loads	*node;

	node = malloc(sizeof(t_loads));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_loads));
	node->command = cmd;
	node->redirect = redir;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	node->hd_buffer = NULL;
	return (node);
}

void	append_node(t_loads **head, char **cmd, char **redir)
{
	t_loads	*new_node;
	t_loads	*cur;
	int		type;

	if (!redir || !redir[0] || !redir[0][0])
		type = 3;
	else if (redir[0][0] == '|')
		type = 1;
	else if (look_hd(redir))
		type = 2;
	else
		type = 4;
	new_node = create_node(cmd, redir, type);
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
	new_node->prev = cur;
}

int	prepare_node(t_loads **loads, t_tokens **tmp)
{
	char		**cmd;
	char		**redir;
	t_tokens	*cur;

	cmd = NULL;
	redir = NULL;
	cur = *tmp;
	while (cur && cur->type != 1)
	{
		if (cur->type == 6)
			cmd = add_token(cmd, cur->token);
		else
			redir = add_token(redir, cur->token);
		cur = cur->next;
	}
	*tmp = cur;
	append_node(loads, cmd, redir);
	return (0);
}
