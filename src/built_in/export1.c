/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:11:17 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 02:11:17 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_alpha(t_envir *envi)
{
	t_envir	*e;
	t_envir	*c;
	int		index;

	e = envi;
	while (e)
	{
		index = 0;
		c = envi;
		while (c)
		{
			if (ft_strcmp(e->key, c->key) > 0)
				index++;
			c = c->next;
		}
		e->index = index;
		e = e->next;
	}
}

int	is_valid(char *var)
{
	int	i;

	i = 0;
	if (var[0] == '=')
	{
		printf("export: %c : not a valid identifier\n", var[i]);
		return (1);
	}
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalpha(var[0]) || !(ft_isalnum(var[i])))
		{
			printf("export: %c : not a valid identifier\n", var[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export_args(t_envir *envi, t_info *info, char **v,
		int *flag)
{
	int		i;
	int		len;
	t_envir	*envvar;

	envvar = NULL;
	i = 1;
	while (v[i])
	{
		len = findvarlen(v[i]);
		envvar = does_exist(envi, v[i], len);
		if (envvar && v[i][len] == '=')
			replace_envlist(envvar, v[i] + len + 1);
		else if (!envvar)
		{
			if (is_valid(v[i]) == 0)
			{
				info->len_envvar++;
				add_env(&envi, v[i], info->len_envvar);
			}
			else
				(*flag)++;
		}
		i++;
	}
	return (0);
}

int	export_noarg(t_envir *envi, t_info *info)
{
	int		i;
	t_envir	*c;

	i = 0;
	printf("hi\n");
	sort_alpha(envi);
	while (i < info->len_envvar)
	{
		c = envi;
		while (c)
		{
			if (c->index == i)
			{
				if (c->val[0] != '\0')
					printf("declare -x %s=\"%s\"\n", c->key, c->val);
				else
					printf("declare -x %s%s\n", c->key, c->val);
				break ;
			}
			c = c->next;
		}
		i++;
	}
	return (0);
}

int	export(t_envir **envi, t_info **info, char **argv)
{
	int	flag;

	flag = 0;
	if (argv[1] == NULL)
		export_noarg(*envi, *info);
	else
		export_args(*envi, *info, argv, &flag);
	if (flag > 0)
		return (1);
	return (0);
}
