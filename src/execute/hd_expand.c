/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:00:38 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:59:24 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isqouted(char *del)
{
	size_t	len;

	len = ft_strlen(del);
	if (!del || len < 2)
		return (0);
	return ((del[0] == '"' && del[len - 1] == '"')
		|| (del[0] == '\'' && del[len - 1] == '\''));
}

char	*append_line(char *buf, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(buf, line);
	if (!tmp)
		return (NULL);
	free(buf);
	return (tmp);
}

char	*expand_ds_var(t_envir *envi, char *line, int *i, int start)
{
	int		len;
	char	*var;
	char	*value;

	len = 0;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	var = ft_substr(line, start, len);
	if (!var)
		return (NULL);
	value = find_replace(envi, var);
	free(var);
	return (value);
}

char	*expand_ds_line(t_shell *shell, t_envir *envi, char *line, int *i)
{
	int	start;

	start = *i;
	if (line[start] == '?')
		return (expand_es(shell, i));
	if (ft_isdigit(line[start]) && line[start] != '0')
	{
		(*i)++;
		return (NULL);
	}
	if (line[start] == '0')
	{
		(*i)++;
		return (ft_strdup("./minishell"));
	}
	return (expand_ds_var(envi, line, i, start));
}

char	*expand_line(t_shell *shell, t_envir *envi, char *line)
{
	int		i;
	char	*value;
	char	*var;

	i = 0;
	value = ft_strdup("");
	var = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			var = expand_ds_line(shell, envi, line, &i);
			if (var)
			{
				joining(&value, var);
				free(var);
			}
		}
		else
			add_char(&value, line[i], &i);
	}
	return (value);
}
