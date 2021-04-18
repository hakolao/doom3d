/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:08:44 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:47:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_memchr() function locates the first occurrence of
** c (converted to an unsigned char) in string s..
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cpy;

	cpy = (unsigned char*)s;
	while (n--)
	{
		if (*cpy == (unsigned char)c)
			return (cpy);
		cpy++;
	}
	return (NULL);
}
