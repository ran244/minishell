/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:13:54 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 17:05:29 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_dir(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**split;

	i = 0;
	k = 0;
	split = (char **)malloc(sizeof(char *) * (PATH_MAX));
	if (!split)
		return (NULL);
	while (str[i])
	{
		j = 0;
		split[k] = (char *)malloc(sizeof(char) * (PATH_MAX));
		if (!split[k])
			return (NULL);
		while (str[i] != ' ' && str[i] != '\t' && str[i] != ':' && str[i])
			split[k][j++] = str[i++];
		while (str[i] == ' ' || str[i] == '\t' || str[i] == ':')
			i += 1;
		split[k++][j] = '\0';
	}
	split[k] = NULL;
	return (split);
}

char	*get_path_value(t_envir *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (NULL);
}

char	*get_command_path_if_direct(char *cmd)
{
	if (is_path(cmd))
		return (ft_strdup(cmd));
	return (NULL);
}

char	*search_in_path(char **paths, char *cmd)
{
	int		i;
	char	*test;
	char	*command;
	char	*result;

	i = 0;
	test = NULL;
	command = ft_strjoin("/", cmd);
	result = NULL;
	while (paths && paths[i])
	{
		free(test);
		test = ft_strjoin(paths[i], command);
		if (access(test, X_OK) == 0)
		{
			result = ft_strdup(test);
			break ;
		}
		i++;
	}
	free(test);
	free(command);
	return (result);
}

char	*full_path(char *cmd, t_envir *env)
{
	char	*path_value;
	char	*direct_path;
	char	*result;
	char	**paths;

	path_value = get_path_value(env);
	direct_path = get_command_path_if_direct(cmd);
	result = NULL;
	if (direct_path)
	{
		free(path_value);
		return (direct_path);
	}
	if (!path_value)
		return (NULL);
	paths = ft_split_dir(path_value);
	free(path_value);
	result = search_in_path(paths, cmd);
	free_2d_array(paths);
	return (result);
}
