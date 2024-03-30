/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:31:26 by aghergho          #+#    #+#             */
/*   Updated: 2024/03/29 01:42:42 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

char	*str_sub(char *str, int len)
{
	char	*s;
	int		i;

	if (!len)
		len++;
	s = (char *) malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

//checking the end_of_line
int	check_end_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '\n')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}