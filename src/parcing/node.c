/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:49:09 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 02:00:48 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addback(t_tokens **list, t_tokens *tmp)
{
	t_tokens	*tail;

	if (*list == NULL)
	{
		*list = tmp;
		tmp->prev = NULL;
		tmp->tail = tmp;
	}
	else
	{
		tail = (*list)->tail;
		tail->next = tmp;
		tmp->prev = tail;
		tmp->next = NULL;
		(*list)->tail = tmp;
	}
}

void	assign_type(t_tokens **tmp)
{
	if (!(*tmp)->prev)
	{
		(*tmp)->type = 6;
		return ;
	}
	if ((*tmp)->prev->type == 4)
		(*tmp)->type = 44;
	else if ((*tmp)->prev->type == 5)
		(*tmp)->type = 55;
	else if ((*tmp)->prev->type == 2)
		(*tmp)->type = 22;
	else if ((*tmp)->prev->type == 3)
		(*tmp)->type = 33;
	else
		(*tmp)->type = 6;
}

void	add_node(t_envir **envi, t_envir *tmp)
{
	t_envir	*tail;

	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->tail = NULL;
	if (*envi == NULL)
	{
		*envi = tmp;
		tmp->tail = tmp;
	}
	else
	{
		tail = (*envi)->tail;
		tail->next = tmp;
		tmp->prev = tail;
		(*envi)->tail = tmp;
	}
}

void	delete_node(t_envir **head, t_envir *node)
{
	if (!head || !*head || !node)
		return ;
	if (node == (*head)->tail)
	{
		if (node->prev)
			(*head)->tail = node->prev;
		else
			(*head)->tail = NULL;
	}
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->key);
	free(node->val);
	free(node);
}

int	add(t_tokens **list, char *command, int ty)
{
	t_tokens	*tmp;

	tmp = malloc(sizeof(t_tokens));
	if (!tmp)
		return (-1);
	ft_memset(tmp, 0, sizeof(t_tokens));
	tmp->token = ft_strdup(command);
	tmp->type = ty;
	addback(list, tmp);
	if (tmp->type == 6)
		assign_type(&tmp);
	return (0);
}
