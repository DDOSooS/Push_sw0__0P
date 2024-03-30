/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 06:25:55 by wzon              #+#    #+#             */
/*   Updated: 2024/03/30 07:08:49 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

t_ps    *ft_get_min(t_ps *stack)
{
    t_ps    *t_tmp;
    t_ps    *t_min;

    t_min = stack;
    t_tmp = stack->next;
    while (t_tmp)
    {
        if (t_min->integer > t_tmp->integer)
            t_min = t_tmp;
        t_tmp = t_tmp->next;
    }
    return (t_min);
}

t_ps    *ft_get_max(t_ps *stack)
{
    t_ps    *t_tmp;
    t_ps    *t_max;

    t_max = stack;
    t_tmp = stack->next;
    while (t_tmp)
    {
        if (t_max->integer < t_tmp->integer)
            t_max = t_tmp;
        t_tmp = t_tmp->next;
    }
    return (t_max);
}

int ft_chek_mid_point(t_ps *node, t_ps *stack)
{
	int		len;
	int		position;
	
	len = ft_stack_len(stack);
	position = ft_get_position(node, stack);
	if (len / 2 >= position)
		return (0);
	return (1);
}

int ft_calculate_cost(t_ps *node, t_ps *stack)
{
    int cost;
    int len;
    int position;

    cost = 0;
    len = ft_stack_len(stack);
    position = ft_get_position(node, stack);
    if (len / 2 >= position)
        cost = position;
    else
        cost = len - position;
    return (cost);
}

void    ft_finish_exec(t_ps *cheapest, t_ps *target, t_ps **a, t_ps **b)
{
    int moves1;
    int moves2;
    
    cheapest->midpoint = ft_chek_mid_point(cheapest, *a);
    target->midpoint = ft_chek_mid_point(target, *b);
    moves1 = ft_calculate_cost(cheapest, *a);
    moves2 = ft_calculate_cost(target, *b);
    if (cheapest->midpoint)
    {
        while (moves1--)
            ft_rra(a,1);
    }
    else if (! cheapest->midpoint)
        while (moves1--)
            ft_ra(a, 1);
    if (target->midpoint)
    {
        while (moves2--)
            ft_rrb(b, 1);
    }
    else if (! target->midpoint)
        while (moves2--)
            ft_rb(b, 1);   
}