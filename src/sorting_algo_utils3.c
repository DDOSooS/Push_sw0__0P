/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algo_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:10:50 by wzon              #+#    #+#             */
/*   Updated: 2024/03/30 07:11:02 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

t_ps    *ft_get_closest_smaller(t_ps *node, t_ps *stack)
{
    t_ps    *target;
    int     dif;

    dif = 0;
    target = NULL;
    while (stack)
    {
        if (node->integer > stack->integer)
        {
            if (! dif)
            {
                dif = node->integer - stack->integer;
                target = stack;
            }
            else if (dif > node->integer - stack->integer )
            {
                dif = node->integer - stack->integer;
                target = stack;
            }
        }
        stack = stack->next;
    }
    return (target);
}

t_ps    *ft_get_closest_bigger(t_ps *node, t_ps *stack)
{
    t_ps    *target;
    int     dif;

    dif = 0;
    target = NULL;
    while (stack)
    {
        if (node->integer < stack->integer)
        {
            if (! dif)
            {
                dif = stack->integer - node->integer;
                target = stack;
            }
            else if (dif > stack->integer - node->integer )
            {
                dif = stack->integer - node->integer;
                target = stack;
            }
        }
        stack = stack->next;
    }
    return (target);
}