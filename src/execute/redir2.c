/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:12:45 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:53:50 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_in(char *in, int outfd)
{
	int	fd;

	fd = open(in, O_RDONLY);
	if (fd == -1)
		return (-1);
	dup2(fd, outfd);
	close(fd);
	return (0);
}

int	redirection_out(char *out, int infd, int flag)
{
	int	fd;

	fd = 0;
	if (flag == 1)
		fd = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (flag == 2)
		fd = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, infd);
	close(fd);
	return (0);
}

int	write_to_pipe(int *fd, t_loads **load)
{
	if (dup2(fd[1], 1) == -1)
		return (-1);
	(*load)->fd_out = 1;
	close(fd[1]);
	return (0);
}

int	read_from_pipe(int *fd, t_loads **load)
{
	if (dup2(fd[0], 0) == -1)
		return (-1);
	(*load)->fd_in = 0;
	close(fd[0]);
	return (0);
}

void	setup_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}
