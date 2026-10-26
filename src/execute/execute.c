/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:37:16 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 15:56:16 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_std_fds(t_info *info)
{
	dup2(info->stdin_copy, 0);
	dup2(info->stdout_copy, 1);
	close(info->stdin_copy);
	close(info->stdout_copy);
}

void	finalize_exec(t_shell *shell, t_info *info, pid_t *pid, int count)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < count)
	{
		if (i == count - 1)
		{
			waitpid(pid[i], &status, 0);
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		else
			waitpid(pid[i], NULL, 0);
		i++;
	}
	restore_std_fds(info);
	if (pid)
	{
		free(pid);
		pid = NULL;
	}
}

void	move(t_loads **cur)
{
	if ((*cur)->next && (*cur)->next->type == 1)
		(*cur) = (*cur)->next;
	(*cur) = (*cur)->next;
}

int	process_node(t_shell *shell, t_exec_context *ctx)
{
	check_exec(ctx->cur, shell, ctx->fd);
	if (is_solo_builtin(shell, ctx->cur))
		return (handle_solo_builtin(shell, ctx, ctx->cur));
	else
		return (handle_fork(shell, ctx));
}

int	execute(t_shell *shell)
{
	t_exec_context	ctx;

	if (init_exec_context(shell, &ctx) == -1)
		return (-1);
	preprocess_heredoc(shell, shell->envi, shell->loads);
	while (ctx.cur)
	{
		if (process_node(shell, &ctx) == -1)
			break ;
		move(&ctx.cur);
	}
	finalize_exec(shell, shell->info, ctx.pid, ctx.i);
	return (0);
}
