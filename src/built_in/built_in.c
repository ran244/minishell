/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:14:54 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/17 22:15:23 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_envir **envi)
{
	t_envir	*var;

	var = *envi;
	while (var)
	{
		if (ft_strcmp(var->key, "PWD") == 0)
		{
			write(1, var->val, ft_strlen(var->val));
			write(1, "\n", 1);
			break ;
		}
		var = var->next;
	}
	return (1);
}

int	get_parent_len(char *dir)
{
	int	i;

	i = ft_strlen(dir);
	while (i >= 0 && dir[i] != '/')
	{
		i--;
	}
	return (i);
}

int	get_builtin_flag(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "export", 6) == 0
		&& ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0
		&& ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (2);
	else if (ft_strncmp(cmd, "env", 3) == 0
		&& ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (3);
	else if (ft_strncmp(cmd, "pwd", 3) == 0
		&& ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (4);
	else if (ft_strncmp(cmd, "cd", 2) == 0
		&& ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (5);
	else if (ft_strncmp(cmd, "unset", 5) == 0
		&& ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (6);
	else if (ft_strncmp(cmd, "exit", 4) == 0
		&& ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (7);
	return (0);
}

int	is_builtin(char **v)
{
	if (v && v[0])
		return (get_builtin_flag(v[0]));
	return (0);
}

int	execut_built_in(t_shell *shell, t_exec_context *ctx, char **v, int flag)
{
	int	status;

	status = 0;
	if (flag == 1)
		status = export(&shell->envi, &shell->info, v);
	else if (flag == 2)
		status = echo(v);
	else if (flag == 3)
		status = env(&shell->envi);
	else if (flag == 4)
		status = pwd(&shell->envi);
	else if (flag == 5)
		status = cd(&shell->envi, v);
	else if (flag == 6)
		status = unset(&shell->envi, v);
	else if (flag == 7)
		status = mini_exit(&shell, &ctx, v);
	return (status);
}
