/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:07:15 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:55:42 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_tmp(char *del, int flag)
{
	char	*tmp;
	char	*trimmed;

	tmp = ft_strdup(del);
	if (!tmp)
		return (NULL);
	if (flag == 1)
	{
		trimmed = ft_substr(del, 1, ft_strlen(del) - 2);
		free(tmp);
		tmp = trimmed;
	}
	return (tmp);
}

int	is_delimiter(char *line, char *tmp)
{
	if (!line)
		return (1);
	if (ft_strcmp(line, tmp) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	look_hd(char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (ft_strncmp(redir[i], "<<", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	prep_for_execute(t_tokens **list, t_loads **loads)
{
	t_tokens	*tmp;
	char		**pipe;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == 1)
		{
			pipe = malloc(sizeof(char *) * 2);
			pipe[0] = ft_strdup("|");
			pipe[1] = NULL;
			append_node(loads, NULL, pipe);
			tmp = tmp->next;
		}
		else
			prepare_node(loads, &tmp);
	}
	if (list && *list)
		free_tokens(list);
	return (0);
}
