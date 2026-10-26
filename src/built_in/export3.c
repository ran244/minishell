/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bushra <bushra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:58:44 by balhamad          #+#    #+#             */
/*   Updated: 2025/06/18 01:41:16 by bushra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_envlist(t_envir *tmp, char *res)
{
	char	*temp;

	temp = NULL;
	if (tmp->key)
	{
		free(tmp->val);
		tmp->val = ft_strdup(res);
	}
	free(temp);
}
