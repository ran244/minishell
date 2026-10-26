/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:53:49 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 16:56:25 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_tokens **list)
{
	t_tokens	*tmp;

	while (*list)
	{
		tmp = *list;
		(*list) = (*list)->next;
		free(tmp->token);
		free(tmp);
	}
}

int	is_pathy(char *v)
{
	int	i;

	i = 0;
	while (v[i])
	{
		if (v[i] == '/' || v[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

int	ft_perror(int flag, char *str)
{
	if (is_directory(str))
		flag = 4;
	else if (is_pathy(str) == 1)
		flag = 2;
	if (str && str[0])
		ft_putstr_fd(str, 2);
	if (flag == 1)
		ft_putstr_fd(": command not found\n", 2);
	if (flag == 2)
		ft_putstr_fd(": no such file or directory\n", 2);
	if (flag == 3)
		ft_putstr_fd(": permission denied\n", 2);
	if (flag == 4)
	{
		ft_putstr_fd(": is a directory\n", 2);
		return (1);
	}
	return (0);
}

void	ft_exit(t_shell *shell, int exit_stat, int flag, char *str)
{
	shell->exit_status = exit_stat;
	if (str)
	{
		if (ft_perror(flag, str) == 1)
		{
			shell->exit_status = 126;
			exit_stat = 126;
		}
	}
	if (shell->tokens)
		free_tokens(&shell->tokens);
	if (shell->info)
	{
		free_info(shell->info);
	}
	if (shell->envi)
		free_envvar(&shell->envi);
	if (shell->loads)
		free_loads(shell->loads);
	exit(exit_stat);
}

void	ft_exit2(t_tokens **list, t_info **info, t_envir **envi, t_loads **load)
{
	(void)envi;
	(void)info;
	if (list && *list)
		free_tokens(list);
	if (load && *load)
		free_loads(*load);
}
