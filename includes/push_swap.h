/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:30:07 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/30 02:38:04 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <limits.h>
typedef struct push_swap
{
	int					integer;
	int					position;
	int					cost;
	int					midpoint;
	struct push_swap	*next;
	// struct push_swap	*prev;
}	t_ps;


#define BUFFER_SIZE 13

char	*get_next_line(int fd);
int		ft_strlen(char *str);
int		check_end_line(char *str);
char	*str_sub(char *str, int len);

char    **ft_split(char *str);
void    ft_free_mem(char **av);

#endif