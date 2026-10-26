/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:33:44 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 02:01:51 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pipe(t_tokens **list, t_info **info, char *line, int i)
{
	char	*token;

	if (line[i] == '|')
	{
		token = "|";
		add(list, token, 1);
		(*info)->num_of_pipes++;
		i++;
	}
	return (i);
}

int	skip_space(char *line, int i)
{
	while (line[i] == 32)
		i++;
	return (i);
}

int	handle_redirection(t_tokens **list, char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		add(list, "<<", 4);
		return (i + 2);
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		add(list, ">>", 5);
		return (i + 2);
	}
	else
	{
		if (line[i] == '<')
			add(list, "<", 2);
		else
			add(list, ">", 3);
	}
	return (i + 1);
}

int	is_splitter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\0')
		return (1);
	return (0);
}

int	add_env(t_envir **env, char *line, int pi)
{
	t_envir	*tmp;
	int		len;

	tmp = malloc(sizeof(t_envir));
	if (!tmp)
		return (-1);
	len = findvarlen(line);
	tmp->key = ft_substr(line, 0, len);
	tmp->val = ft_substr(line, len + 1, ft_strlen(line) - len);
	if (!tmp->key || !tmp->val)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->val)
			free(tmp->val);
		if (tmp)
			free(tmp);
		return (-1);
	}
	tmp->index = pi;
	add_node(env, tmp);
	return (0);
}
