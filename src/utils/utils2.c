/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:22:47 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 17:09:47 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_loads	*get_head(t_loads *node)
{
	while (node && node->prev)
		node = node->prev;
	return (node);
}

int	ft_strlenn(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			alen;
	unsigned int	slen;
	char			*ptr;

	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if ((slen - start) < len)
		alen = slen - start;
	else
		alen = len;
	ptr = (char *)malloc(alen + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < alen)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	free_copy_env(t_info **info)
{
	int	i;

	i = 0;
	if ((*info)->copy_env)
	{
		while ((*info)->copy_env[i])
		{
			free((*info)->copy_env[i++]);
		}
		free((*info)->copy_env);
	}
}

int	env_var(t_info **info, char **env)
{
	int	i;

	i = 0;
	if (!info)
		return (-1);
	while (env[i])
		i++;
	(*info)->copy_env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!(*info)->copy_env)
		return (-1);
	i = 0;
	while (env[i])
	{
		(*info)->copy_env[i] = ft_strdup(env[i]);
		if (!(*info)->copy_env[i])
			return (-1);
		i++;
	}
	(*info)->copy_env[i] = NULL;
	return (0);
}
