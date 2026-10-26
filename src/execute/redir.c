/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:11:21 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/18 17:07:52 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirect(char *arr)
{
	if (ft_strncmp(arr, "<", 1) == 0 || ft_strncmp(arr, ">", 1) == 0
		|| ft_strncmp(arr, ">>", 2) == 0)
		return (1);
	return (0);
}

int	handle_input_redir(char **redir, int i, t_shell *shell)
{
	if ((!redir[i + 1] || is_redirect(redir[i + 1])) && !shell->redir_flag)
		return (-1);
	if (redirection_in(redir[i + 1], 0) == -1)
	{
		perror(redir[i + 1]);
		return (-1);
	}
	return (2);
}

int	handle_output_redir(char **redir, int i, t_shell *shell, int append)
{
	if ((!redir[i + 1] || is_redirect(redir[i + 1])) && !shell->redir_flag)
		return (-1);
	if (redirection_out(redir[i + 1], 1, append) == -1)
	{
		perror(redir[i + 1]);
		return (-1);
	}
	return (2);
}

int	handle_heredoc_redir(char **redir, int i, t_loads *load, t_shell *shell)
{
	int	pipefd[2];

	if ((!redir[i + 1] || is_redirect(redir[i + 1])) && !shell->redir_flag)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		perror("BULLYSHELL: pipe");
		return (-1);
	}
	write(pipefd[1], load->hd_buffer, ft_strlen(load->hd_buffer));
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("BULLYSHELL: dup2");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (2);
}

int	handle_redi(char **redir, t_loads **load, t_shell *shell)
{
	int	i;
	int	ret;

	i = 0;
	if (!redir || !load)
		return (0);
	while (redir[i])
	{
		if (!ft_strcmp(redir[i], "<"))
			ret = handle_input_redir(redir, i, shell);
		else if (!ft_strcmp(redir[i], ">"))
			ret = handle_output_redir(redir, i, shell, 1);
		else if (!ft_strcmp(redir[i], ">>"))
			ret = handle_output_redir(redir, i, shell, 2);
		else if (!ft_strcmp(redir[i], "<<"))
			ret = handle_heredoc_redir(redir, i, *load, shell);
		else
			return (-1);
		if (ret == -1)
			return (-1);
		i += ret;
	}
	return (0);
}
