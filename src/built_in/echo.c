/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:43:27 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 17:08:04 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_n(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == 'n')
			return (1);
		i++;
	}
	return (0);
}

int	check_n(char *command)
{
	int	j;

	j = 1;
	if (find_n(command) == 0)
		return (0);
	while (command[j])
	{
		if (command[j] != 'e' && command[j] != 'E' && command[j] != 'n')
			break ;
		j++;
	}
	if ((int)ft_strlen(command) == j)
		return (1);
	return (0);
}

int	parse_n_flags(char **cmd, int *start_idx)
{
	int	i;
	int	n_flag;
	int	j;

	i = 1;
	n_flag = 0;
	j = 0;
	while (cmd[i] && (ft_strncmp(cmd[i], "-", 1) == 0))
	{
		n_flag = check_n(cmd[i]);
		if (n_flag == 1)
		{
			j++;
			i++;
		}
		else
			break ;
	}
	*start_idx = i;
	return (j);
}

int	echo(char **cmd)
{
	int	i;
	int	j;

	j = parse_n_flags(cmd, &i);
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (j == 0)
		write(1, "\n", 1);
	return (0);
}
