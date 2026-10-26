/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:54:00 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:44:01 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strchrr(const char *str, int s)
{
	char			c;
	unsigned int	i;

	i = 0;
	c = (char)s;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*fill_line(t_envir *envi)
{
	int		i;
	int		len;
	char	*arr;

	i = 0;
	len = ft_strlen(envi->key);
	arr = malloc(len + 1);
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = envi->key[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

void	freearr(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(arr);
}

char	**copy_env(t_envir *envi, t_info *info)
{
	char	**copied_env;
	int		len;
	t_envir	*tmp;
	int		i;

	len = info->len_envvar;
	printf("%d", info->len_envvar);
	i = 0;
	tmp = envi;
	copied_env = (char **)malloc((len + 1) * sizeof(char *));
	if (!copied_env || !envi)
		return (NULL);
	while (tmp)
	{
		copied_env[i] = ft_strjoin(tmp->key, tmp->val);
		if (!copied_env[i])
		{
			freearr(copied_env);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	copied_env[i] = NULL;
	return (copied_env);
}
