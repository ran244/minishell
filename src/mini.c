/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:59:28 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 16:04:07 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

int	ini_info(t_info **info)
{
	if (!(*info))
		return (-1);
	(*info)->copy_env = NULL;
	(*info)->num_of_pipes = 0;
	(*info)->len_envvar = 0;
	(*info)->flag = 0;
	return (0);
}

void	ini_shell(t_shell *shell, char **env)
{
	shell->tokens = NULL;
	shell->loads = NULL;
	shell->info = ft_calloc(1, sizeof(t_info));
	shell->envi = NULL;
	shell->exit_status = 0;
	shell->redir_flag = 0;
	if (!shell->info)
		free_info(shell->info);
	if (ini_info(&shell->info) == -1)
		ft_exit(shell, 1, 1, NULL);
	if (env_var(&shell->info, env) == -1)
		ft_exit(shell, 1, 1, NULL);
	if (init_env(&shell->envi, &shell->info, env) == -1)
		ft_exit(shell, 1, 1, NULL);
}

void	last_free(t_shell *shell)
{
	if (shell->envi)
		free_envvar(&shell->envi);
	if (shell->info)
		free_info(shell->info);
}

int	start_execute(t_shell *shell, char **rl)
{
	parcing(shell, &shell->envi, &shell->tokens, &shell->info);
	prep_for_execute(&shell->tokens, &shell->loads);
	execute(shell);
	if (shell->loads)
		free_loads(shell->loads);
	shell->loads = NULL;
	if (*rl[0] != '\0')
	{
		g_sig = 0;
		add_history(*rl);
		free(*rl);
	}
	return (0);
}

int	main(int c, char **v, char **env)
{
	char	*rl;
	t_shell	shell;

	(void)c;
	(void)v;
	ini_shell(&shell, env);
	while (1)
	{
		sig_mode(0);
		rl = readline("BULLYSHELL> ");
		es_signal(&shell);
		if (!rl)
			ft_exit(&shell, shell.exit_status, 1, NULL);
		if (t_tokenise(&shell.tokens, &shell.info, rl) == -1)
		{
			add_history(rl);
			free(rl);
			shell.exit_status = 2;
			ft_exit2(&shell.tokens, &shell.info, &shell.envi, &shell.loads);
			continue ;
		}
		start_execute(&shell, &rl);
	}
	last_free(&shell);
	return (0);
}
