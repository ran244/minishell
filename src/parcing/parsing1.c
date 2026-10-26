/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balhamad <balhamad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:52:10 by falhaimo          #+#    #+#             */
/*   Updated: 2025/06/17 22:15:23 by balhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	joining(char **val, char *var)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(*val, var);
	if (!tmp)
		return ;
	free(*val);
	*val = tmp;
}

void	add_char(char **val, char c, int *i)
{
	char	*tmp;
	char	ch[2];

	tmp = NULL;
	ch[0] = c;
	ch[1] = '\0';
	tmp = ft_strjoin(*val, ch);
	if (!tmp)
		return ;
	(*i)++;
	free(*val);
	*val = tmp;
}
