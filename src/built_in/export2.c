/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:56:14 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:50:25 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_env(t_envir **envi, t_info **info, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		(*info)->len_envvar++;
		if (add_env(envi, env[i], (*info)->len_envvar) == -1)
			return (-1);
		i++;
	}
	if (!get_env_val(envi, "OLDPWD"))
	{
		if (add_env(envi, "OLDPWD", ++(*info)->len_envvar) == -1)
			return (-1);
	}
	return (0);
}

void	print_env(t_envir *head)
{
	if (!head)
	{
		printf("The list is empty.\n");
		return ;
	}
	while (head)
	{
		printf("%s=\"%s\"\n", head->key, head->val);
		head = head->next;
	}
	printf("NULL\n");
}

void	free_envvar(t_envir **env_var)
{
	t_envir	*tmp;

	while (*env_var)
	{
		tmp = *env_var;
		(*env_var) = (*env_var)->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
}

int	findvarlen(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

t_envir	*does_exist(t_envir *envi, char *var, int len)
{
	t_envir	*envvar;

	envvar = envi;
	while (envvar)
	{
		if ((ft_strncmp(envvar->key, var, len) == 0)
			&& (ft_strncmp(envvar->key, var, ft_strlen(envvar->key)) == 0)
			&& (var[len] == '=' || var[len] == '\0'))
			return (envvar);
		envvar = envvar->next;
	}
	return (NULL);
}
