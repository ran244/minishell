/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:10:09 by rabusala          #+#    #+#             */
/*   Updated: 2025/06/17 15:08:37 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr( char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little [i] == '\0')
		return ((char *) & (big[i]));
	while ((i < len) && big[i])
	{
		while ((big[i + j] == little[j]) && little[j] && ((i + j) < len))
			j++;
		if (little[j] == '\0')
			return (little);
		i++;
		j = 0;
	}
	return (0);
}
// /*int main(void)
// {
// 	 char	str[]= "hello world";
// 	 char	to_find[] = "o";

// 	printf("%s\n \n", ft_strnstr(str, to_find,10));
// 	//printf("%d\n", strnstr(str, to_find,4));
// 	// to_find = "";
// 	// printf("%s\n", ft_strnstr(str, to_find));
// 	// printf("%s\n", strnstr(str, to_find));
// 	// to_find = "onj";
// 	// printf("%s\n", ft_strnstr(str, to_find));
// 	// printf("%s\n", strnstr(str, to_find));
// 	// str = "hi my name is raneem";
// 	// to_find = " ";
// 	// printf("%s\n", ft_strnstr(str, to_find));
// 	// printf("%s\n", strnstr(str, to_find));
// }
