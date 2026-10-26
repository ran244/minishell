/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:20:41 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 16:56:50 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	handle_solo_builtin(t_shell *shell, t_exec_context *ctx, t_loads *cur)
{
	if (cur->redirect && handle_redi(cur->redirect, &cur, shell) == -1)
		return (-1);
	shell->exit_status = execut_built_in(shell, ctx, cur->command,
			shell->info->flag);
	return (0);
}

int	is_solo_builtin(t_shell *shell, t_loads *cur)
{
	return (cur->command && shell->info->flag != 0 && !cur->prev && !cur->next);
}

int	is_path(char *v)
{
	if (v[0] == '.' || v[0] == '/')
		return (1);
	return (0);
}

void	free_them_all(t_shell *shell, char *str, pid_t **pid, int exit)
{
	if (*pid)
		free(*pid);
	close(shell->info->stdin_copy);
	close(shell->info->stdout_copy);
	ft_exit(shell, exit, 1, str);
}
