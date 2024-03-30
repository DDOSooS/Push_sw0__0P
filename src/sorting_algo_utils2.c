/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algo_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 06:31:14 by wzon              #+#    #+#             */
/*   Updated: 2024/03/30 07:03:07 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int ft_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

/*
    @return (int)
    check the cheap cost in stack_a and push it to stack_b
    how to calculate the cheapest node ?
    it the combination of the cost of the current node and its target
    cost = curr_cost + target_cost;
    cost = how many move to the node the to top of the stack
*/
int ft_count_cost(t_ps *node, t_ps *a, t_ps *b)
{
    t_ps    *target;
    int     cost;
    
    cost = 0;
    target = ft_get_target(node, b, 0);
    node->midpoint = ft_chek_mid_point(node, a);
    target->midpoint = ft_chek_mid_point(target, b);
    node->cost = ft_calculate_cost(node, a);
    target->cost = ft_calculate_cost(target, b);
    if (node->midpoint && target->midpoint)
        cost = ft_max(node->cost , target->cost);
    else if (!node->midpoint && !target->midpoint)
        cost = ft_max(node->cost, target->cost);
    else
        cost = node->cost + target->cost;
    return (cost);
}

t_ps    *ft_search_cheapest(t_ps *a, t_ps *b)
{
    t_ps    *t_tmp;
    t_ps    *cheapest;

    cheapest = a;
    cheapest->cost = ft_count_cost(cheapest, a, b);
    t_tmp = a->next;
    while (t_tmp)
    {
        t_tmp->cost = ft_count_cost(t_tmp , a, b);
        if (cheapest->cost > t_tmp->cost)
            cheapest = t_tmp;
        t_tmp = t_tmp->next;
    }
    return (cheapest);
}

t_ps    *ft_get_target(t_ps *node, t_ps *stack, int flag)
{
    t_ps    *target;

    if (!flag)
    {
        target = ft_get_closest_smaller(node, stack);
        if  (!target)
            target = ft_get_max(stack);
    }
    else
    {
        target = ft_get_closest_bigger(node, stack);
        if (!target)
            target = ft_get_min(stack);
    }
    return (target);
}