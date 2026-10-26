/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:44:18 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 17:07:17 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_parent_dir(char *dir)
{
	int		i;
	char	*parent_dir;

	i = get_parent_len(dir);
	parent_dir = NULL;
	parent_dir = ft_substr(dir, 0, i);
	if (!parent_dir)
	{
		free(parent_dir);
		return (NULL);
	}
	return (parent_dir);
}

int	change_pd(t_envir **envi, char *target, char *cwd)
{
	char	*oldpwd;
	char	cw[4096];

	oldpwd = NULL;
	oldpwd = ft_strdup(cwd);
	if (chdir(target) != 0)
	{
		perror(target);
		free(oldpwd);
		return (1);
	}
	set_env(envi, "OLDPWD", oldpwd);
	if (getcwd(cw, sizeof(cw)) != NULL)
		set_env(envi, "PWD", cw);
	else
		perror("cd: getcwd after chdir");
	free(oldpwd);
	return (0);
}

char	*decide_target(t_envir **envi, char **v, char *cwd)
{
	char	*target;

	target = NULL;
	if (!v[1])
		target = ft_strdup(get_env_val(envi, "HOME"));
	else if (ft_strcmp(v[1], "..") == 0)
		target = (get_parent_dir(cwd));
	else
		target = ft_strdup(v[1]);
	return (target);
}

void	free_things(char **target, char **cwd)
{
	if (*target)
		free(*target);
	if (*cwd)
		free(*cwd);
}

int	cd(t_envir **envi, char **v)
{
	char	*cwd;
	char	*target;

	target = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("cd : getcwd");
		return (1);
	}
	target = decide_target(envi, v, cwd);
	if (!target)
	{
		free(target);
		free(cwd);
		return (1);
	}
	if (change_pd(envi, target, cwd) == 1)
	{
		free_things(&target, &cwd);
		return (1);
	}
	free_things(&target, &cwd);
	return (0);
}
