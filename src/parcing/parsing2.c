/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:47:26 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 02:04:23 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_replace(t_envir *envi, char *var)
{
	t_envir	*envvar;
	char	*expanded;

	envvar = envi;
	expanded = NULL;
	while (envvar)
	{
		if (ft_strcmp(envvar->key, var) == 0 && envvar->val)
		{
			expanded = ft_strdup(envvar->val);
			return (expanded);
		}
		envvar = envvar->next;
	}
	return (NULL);
}

char	*expand_es(t_shell *shell, int *i)
{
	char	*arr;

	arr = NULL;
	arr = ft_itoa(shell->exit_status);
	if (!arr)
		return (NULL);
	(*i)++;
	return (arr);
}

char	*expand_ds_special(t_shell *shell, t_tokens *list, int *i)
{
	char	*value;

	value = NULL;
	if (list->token[*i] == '?')
	{
		value = expand_es(shell, i);
		return (value);
	}
	if (ft_isdigit(list->token[*i]) && list->token[*i] != '0')
	{
		(*i)++;
		return (NULL);
	}
	if (list->token[*i] == '0')
	{
		value = ft_strdup("./minishell");
		(*i)++;
		return (value);
	}
	return (NULL);
}

char	*expand_ds(t_shell *shell, t_envir *envi, t_tokens *list, int *i)
{
	int		len;
	char	*var;
	char	*value;
	int		start;

	len = 0;
	var = NULL;
	value = NULL;
	start = *i;
	value = expand_ds_special(shell, list, i);
	if (value || list->token[start] == '?' || ft_isdigit(list->token[start]))
		return (value);
	while (list->token[*i] && (ft_isalnum(list->token[*i])
			|| list->token[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	var = ft_substr(list->token, start, len);
	if (!var)
		return (NULL);
	value = find_replace(envi, var);
	free(var);
	return (value);
}

char	*expand_dq(t_shell *shell, t_envir *envi, t_tokens *list, int *i)
{
	char	*value;
	char	*var;

	var = NULL;
	value = ft_strdup("");
	if (!value)
		return (NULL);
	while (list->token[*i] && list->token[*i] != '"')
	{
		if (list->token[*i] == '$')
		{
			(*i)++;
			var = expand_ds(shell, envi, list, i);
			if (var)
			{
				joining(&value, var);
				free(var);
			}
		}
		else
			add_char(&value, list->token[*i], i);
	}
	(*i)++;
	return (value);
}
