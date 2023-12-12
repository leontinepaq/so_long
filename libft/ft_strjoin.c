/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:13:07 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/11/15 15:29:04 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_res;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	str_res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str_res == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str_res[i + j] = s2[j];
		j++;
	}
	str_res[i + j] = '\0';
	return (str_res);
}

/*
#include <stdio.h>

int main ()
{
	printf("%s", ft_strjoin("abc", "defg"));
	return 0;
}
*/
