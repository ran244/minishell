/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:49:14 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:41:50 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_v_len(char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i++;
	return (i);
}

int	is_valid_arg(char *v)
{
	int	i;

	i = 0;
	if (v[0] == '+')
		i++;
	while (v[i])
	{
		if (ft_isdigit(v[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

int	mini_exit(t_shell **shell, t_exec_context **ctx, char **v)
{
	if (v[1] && is_valid_arg(v[1]) == -1)
	{
		printf("BULLYSHELL: exit: %s: numeric argument required\n", v[1]);
		(*shell)->exit_status = 2;
		free_them_all(*shell, NULL, &(*ctx)->pid, (*shell)->exit_status);
		return (0);
	}
	else if (find_v_len(v) > 2)
	{
		printf("BULLYSHELL: exit: too many arguments\n");
		return (1);
	}
	else if (v[1] && is_valid_arg(v[1]) != -1)
		(*shell)->exit_status = ft_atoi(v[1]);
	free_them_all(*shell, NULL, &(*ctx)->pid, (*shell)->exit_status);
	return (0);
}
