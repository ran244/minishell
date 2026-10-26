/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:10:34 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 01:14:50 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_parent(int sig)
{
	if (sig)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = sig;
	}
}

void	sigint_child(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	after_child(int sig)
{
	g_sig = sig;
}

void	sig_mode(int sig)
{
	if (sig == 0)
	{
		signal(SIGINT, sigint_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 1)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, SIG_DFL);
	}
	if (sig == 2)
	{
		signal(SIGINT, after_child);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	es_signal(t_shell *shell)
{
	if (g_sig == SIGINT)
	{
		shell->exit_status = g_sig + 128;
		g_sig = 0;
	}
}
