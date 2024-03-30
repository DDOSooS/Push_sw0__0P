/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algo_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 06:29:46 by wzon              #+#    #+#             */
/*   Updated: 2024/03/30 07:53:08 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"




int ft_stack_len(t_ps *stack)
{
    int len;

    len = 0;
    while (stack)
    {
        len++;
        stack = stack->next;
    }
    return (len);
}

int ft_get_position(t_ps *node, t_ps *stack)
{
    int index;

    index = 0;
    while (stack)
    {
        if (stack->integer == node->integer)
            return (index);
        index++;
        stack = stack->next;
    }
    return (index);
}

void    ft_sort_three(t_ps **stack)
{
    t_ps *t_tmp;

    t_tmp = ft_get_max(*stack);
    if ((*stack)->integer == t_tmp->integer)
        ft_ra(stack, 1);
    else if ((*stack)->next->integer == t_tmp->integer)
        ft_rra(stack, 1);
    if ((*stack)->integer > (*stack)->next->integer)
        ft_sa(stack , 1);
} 