/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:10:13 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 16:03:12 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_closure(char *line, int i, char q)
{
	while (line[i])
	{
		if (line[i] == q)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	handle_qoute_in_word(t_tokens **list, char *line, int i, char q)
{
	int	len;

	len = 0;
	(void)list;
	if (!find_closure(line, i + 1, q))
	{
		if (line[i] == q)
		{
			i++;
			len++;
			while (line[i] != q)
			{
				len++;
				i++;
			}
			return (len + 1);
		}
	}
	else
		printf("syntax error\n");
	return (len);
}

int	handle_word(t_tokens **list, char *line, int i)
{
	char	*w_token;
	int		j;
	int		start;

	start = i;
	j = 0;
	while (line[i] && !is_splitter(line[i]))
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			j = handle_qoute_in_word(list, line, i, line[i]);
			if (j == 0)
				return (-1);
			i += j;
		}
		else if (!is_splitter(line[i]) && line[i] != '"' && line[i] != '\'')
			i++;
	}
	w_token = ft_substr(line, start, i - start);
	if (!w_token)
		return (-1);
	add(list, w_token, 6);
	free(w_token);
	return (i);
}

int	syntax_error(t_tokens **list)
{
	t_tokens	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == 1 && tmp->prev == NULL)
			return (-1);
		if (tmp->type == 1 && tmp->next == NULL)
			return (-1);
		if (tmp->type == 1 && tmp->next->type == 1)
			return (-1);
		if ((tmp->type == 2 && !tmp->next) || (tmp->type == 3 && !tmp->next)
			|| (tmp->type == 4 && !tmp->next) || (tmp->type == 5 && !tmp->next))
			return (-1);
		if ((tmp->type == 2 && tmp->next && tmp->next->type != 22)
			|| (tmp->type == 3 && tmp->next && tmp->next->type != 33)
			|| (tmp->type == 4 && tmp->next && tmp->next->type != 44)
			|| (tmp->type == 5 && tmp->next && tmp->next->type != 55))
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	t_tokenise(t_tokens **list, t_info **info, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = skip_space(line, i);
		if (line[i] == '|')
			i = handle_pipe(list, info, line, i);
		if (line[i] == '<' || line[i] == '>')
			i = handle_redirection(list, line, i);
		if (!is_splitter(line[i]))
			i = handle_word(list, line, i);
		if (i == -1)
			return (-1);
	}
	if (syntax_error(list) == -1)
	{
		printf("syntax error near unexpected token\n");
		return (-1);
	}
	return (1);
}
