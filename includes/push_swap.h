/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:30:07 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/26 00:45:29 by wzon             ###   ########.fr       */
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
	int					cost;
	int					midpoint;
	int					sa;
	int					sb;
	int					ss;
	int					pa;
	int					pb;
	int					ra;
	int					rb;
	int					rr;
	int					rra;
	int					rrb;
	int					rrr;
	struct push_swap	*next;
	// struct push_swap	*prev;
}	t_ps;

char    **ft_split(char *str);
void    ft_free_mem(char **av);
int		ft_strlen(char *str);

#endif