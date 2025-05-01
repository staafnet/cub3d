/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:35:42 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/29 13:48:53 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2 || *s1 == '\0')
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
