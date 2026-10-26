/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:25:18 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 02:05:38 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_info(t_info *info)
{
	int	i;

	i = 0;
	if (info->copy_env)
	{
		while (info->copy_env[i])
		{
			free(info->copy_env[i]);
			i++;
		}
		free(info->copy_env);
	}
	free(info);
}

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_loads(t_loads *loads)
{
	t_loads	*next;
	t_loads	*tmp;

	tmp = get_head(loads);
	while (tmp)
	{
		next = tmp->next;
		if (tmp->command)
			free_2d_array(tmp->command);
		if (tmp->redirect)
			free_2d_array(tmp->redirect);
		if (tmp->hd_buffer)
			free(tmp->hd_buffer);
		free(tmp);
		tmp = next;
	}
}
