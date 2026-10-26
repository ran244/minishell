/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:18:08 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 16:51:33 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_shell *shell, t_exec_context *ctx, t_loads *cur,
				pid_t *pid)
{
	char	*path;
	int		status;

	status = 0;
	path = NULL;
	if (cur->redirect && handle_redi(cur->redirect, &cur, shell) == -1)
		free_them_all(shell, NULL, &pid, 1);
	if (!cur->command || !cur->command[0])
		free_them_all(shell, NULL, &pid, 1);
	if (shell->info->flag)
	{
		status = execut_built_in(shell, ctx, cur->command, shell->info->flag);
		free_them_all(shell, NULL, &pid, status);
	}
	path = full_path(cur->command[0], shell->envi);
	if (!path)
	{
		free(path);
		free_them_all(shell, cur->command[0], &pid, 127);
	}
	execve(path, cur->command, shell->info->copy_env);
	free(path);
	free_them_all(shell, cur->command[0], &pid, 127);
}

void	parent_cleanup(int *prev_fd, t_loads *cur, int *fd, pid_t pid)
{
	(void)pid;
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cur->next && cur->next->type == 1)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}

int	get_command_num(t_loads **load)
{
	t_loads	*cur;
	int		len;

	cur = *load;
	len = 0;
	while (cur)
	{
		if (cur->command || cur->redirect)
			len++;
		cur = cur->next;
	}
	return (len);
}

void	clean_child(t_shell *shell, t_exec_context *ctx)
{
	(void)shell;
	if (ctx->pid)
		free(ctx->pid);
}

int	handle_fork(t_shell *shell, t_exec_context *ctx)
{
	ctx->pid[ctx->i] = fork();
	if (ctx->pid[ctx->i] == 0)
	{
		sig_mode(1);
		prep_child(ctx->cur, ctx->prev_fd, ctx->fd);
		child_process(shell, ctx, ctx->cur, ctx->pid);
	}
	sig_mode(2);
	parent_cleanup(&ctx->prev_fd, ctx->cur, ctx->fd, ctx->pid[ctx->i]);
	ctx->i++;
	return (0);
}
