/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:47:47 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 02:13:24 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_envir **envi)
{
	t_envir	*env;

	env = *envi;
	while (env)
	{
		if (env->val[0] != '\0')
			printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
	return (0);
}

char	*get_env_val(t_envir **envi, char *key)
{
	t_envir	*var;

	var = *envi;
	while (var)
	{
		if (ft_strncmp(var->key, key, ft_strlen(key)) == 0
			&& ft_strncmp(var->key, key, ft_strlen(var->key)) == 0)
			return (var->val);
		var = var->next;
	}
	return (NULL);
}

int	set_env(t_envir **envi, char *key, char *res)
{
	t_envir	*var;

	var = *envi;
	while (var)
	{
		if (ft_strncmp(var->key, key, ft_strlen(key)) == 0
			&& ft_strncmp(var->key, key, ft_strlen(var->key)) == 0)
		{
			replace_envlist(var, res);
			break ;
		}
		var = var->next;
	}
	return (1);
}

int	unset(t_envir **envi, char **v)
{
	int		i;
	t_envir	*envvar;

	i = 0;
	if (!v)
		return (0);
	while (v[i])
	{
		envvar = does_exist(*envi, v[i], ft_strlen(v[i]));
		if (envvar)
			delete_node(envi, envvar);
		i++;
	}
	return (0);
}
