/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:31:07 by akyoshid          #+#    #+#             */
/*   Updated: 2024/11/19 17:59:33 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// === DESCRIPTION ===
// Compare the null-terminated strings s1 and s2 not more than n characters.
// Characters that appear after a ‘\0’ character are not compared.

// === RETURN VALUES ===
// Return s1 - s2.
// If s1 and s2 are identical, return 0.
// Use unsigned characters for comparison, so that ‘\200’ is greater than ‘\0’.

#include "../../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		if (str1[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	str1[] = "abc\200";
// 	char	str2[] = "abc";

// 	printf("%d\n", ft_strncmp(str1, str2, 5));
// 	printf("%d\n", strncmp(str1, str2, 5));
// 	return (0);
// }
