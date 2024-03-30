/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_cmd2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 06:24:16 by wzon              #+#    #+#             */
/*   Updated: 2024/03/30 08:14:00 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/push_swap_bonus.h"

void    ft_rrr(t_ps **stack_a, t_ps **stack_b, int flag)
{
    ft_rra(stack_a, 0);
    ft_rrb(stack_b, 0);
    if (flag)
        write(1, "rrr\n", 4);
}