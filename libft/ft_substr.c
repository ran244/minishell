/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:05:45 by rabusala          #+#    #+#             */
/*   Updated: 2025/06/17 15:06:29 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	size_t			i;
	size_t			alen;
	unsigned int	slen;
	char			*ptr;

	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if ((slen - start) < len)
		alen = slen - start;
	else
		alen = len;
	ptr = (char *)malloc(alen + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < alen)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main(void)
// {
// 	const char str[]="var";
// 	printf("%s\n", str);
// 	char *com=ft_substr(str,3,ft_strlen(str)-3);
// 	printf("%s\n",com);
// 	return 0;
// }
