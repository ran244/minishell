/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:08:45 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:55:02 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	yalla_init(t_shell *shell, int *prev_fd, int *i, int **pid)
{
	*i = 0;
	shell->info->stdin_copy = dup(0);
	shell->info->stdout_copy = dup(1);
	*prev_fd = -1;
	(*pid) = malloc(sizeof(pid_t) * get_command_num(&shell->loads));
	if (!(*pid))
		return (-1);
	return (0);
}

int	init_exec_context(t_shell *shell, t_exec_context *ctx)
{
	ctx->cur = shell->loads;
	ctx->i = 0;
	if (yalla_init(shell, &ctx->prev_fd, &ctx->i, &ctx->pid) == -1)
		return (-1);
	return (0);
}

void	check_exec(t_loads *cur, t_shell *shell, int *fd)
{
	if (cur->command)
		shell->info->flag = is_builtin(cur->command);
	if (cur->next && cur->next->type == 1)
		setup_pipe(fd);
}

int	prep_child(t_loads *cur, int prev_fd, int *fd)
{
	int	i;

	i = 3;
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (cur->next && cur->next->type == 1)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	while (i < 1024)
	{
		close(i);
		i++;
	}
	return (0);
}
