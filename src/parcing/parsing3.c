/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:48:12 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 17:10:17 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_sq(t_tokens *list, int *i)
{
	char	*value;

	value = ft_strdup("");
	if (!value)
		return (NULL);
	while (list->token[*i] && list->token[*i] != '\'')
	{
		add_char(&value, list->token[*i], i);
	}
	(*i)++;
	return (value);
}

void	hehe(t_shell *shell, t_tokens *list, int *i,
		char **value)
{
	char	*var;

	var = NULL;
	(*i)++;
	if (list->token[(*i) - 1] == '"')
		var = expand_dq(shell, shell->envi, list, i);
	else if (list->token[(*i) - 1] == '$')
		var = expand_ds(shell, shell->envi, list, i);
	else if (list->token[(*i) - 1] == '\'')
		var = expand_sq(list, i);
	if (var)
	{
		joining(value, var);
		free(var);
	}
}

char	*expand(t_shell *shell, t_envir *eniv, t_tokens *list, t_info *info)
{
	int		i;
	char	*value;

	(void)info;
	(void)eniv;
	i = 0;
	value = ft_strdup("");
	if (!value)
		return (NULL);
	while (list->token[i])
	{
		if (list->token[i] == '"'
			|| list->token[i] == '\'' || list->token[i] == '$')
		{
			shell->redir_flag = 1;
			hehe(shell, list, &i, &value);
		}
		else
			add_char(&value, list->token[i], &i);
	}
	return (value);
}

int	parcing(t_shell *shell, t_envir **eniv, t_tokens **list, t_info **info)
{
	t_tokens	*tmp;
	char		*result;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type != 44)
		{
			result = expand(shell, *eniv, tmp, *info);
			replace_token(tmp, result);
			free(result);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

void	replace_token(t_tokens *tmp, char *res)
{
	if (tmp->token)
	{
		free(tmp->token);
		tmp->token = ft_strdup(res);
	}
}
