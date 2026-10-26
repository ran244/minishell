/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:03:48 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:53:03 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_if_needed(char *line, int flag,
							t_shell *shell, t_envir *env)
{
	char	*expanded;

	if (flag == 0)
	{
		expanded = expand_line(shell, env, line);
		free(line);
		return (expanded);
	}
	return (line);
}

char	*append_and_check(char *buf, char *line, char *tmp)
{
	buf = append_line(buf, line);
	buf = append_line(buf, "\n");
	free(line);
	if (!buf)
	{
		free(tmp);
		return (NULL);
	}
	return (buf);
}

char	*hd_loop(t_shell *shell, t_envir *env, char *del, int flag)
{
	char	*line;
	char	*buf;
	char	*tmp;

	buf = ft_strdup("");
	tmp = init_tmp(del, flag);
	if (!buf || !tmp)
		return (free(buf), free(tmp), NULL);
	while (1)
	{
		line = readline("> ");
		if (is_delimiter(line, tmp))
			break ;
		line = expand_if_needed(line, flag, shell, env);
		if (!line)
			return (free(tmp), free(buf), NULL);
		buf = append_and_check(buf, line, tmp);
		if (!buf)
			return (NULL);
	}
	free(tmp);
	return (buf);
}

char	*read_hd(t_shell *shell, t_envir *envi, char **redirect)
{
	int		i;
	char	*content;
	char	*new_content;

	i = 0;
	content = NULL;
	while (redirect && redirect[i])
	{
		if (ft_strncmp(redirect[i], "<<", 2) == 0 && redirect[i + 1])
		{
			new_content = hd_loop(shell, envi, redirect[i + 1],
					isqouted(redirect[i + 1]));
			if (!new_content)
			{
				free(content);
				return (NULL);
			}
			free(content);
			content = new_content;
			i += 2;
		}
		else
			i++;
	}
	return (content);
}

int	preprocess_heredoc(t_shell *shell, t_envir *envi, t_loads *load)
{
	t_loads	*cur;

	cur = load;
	while (cur)
	{
		if (cur->type == 2)
		{
			cur->hd_buffer = read_hd(shell, envi, cur->redirect);
			if (!cur->hd_buffer)
			{
				perror("HD malloc failed");
				return (-1);
			}
		}
		cur = cur->next;
	}
	return (0);
}
