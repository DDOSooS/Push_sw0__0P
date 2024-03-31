/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algo_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:10:50 by wzon              #+#    #+#             */
/*   Updated: 2024/03/31 14:37:32 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

t_ps    *ft_get_closest_smaller(t_ps *node, t_ps *stack)
{
    t_ps    *closest_smaller;
    
    closest_smaller = NULL;
    while (stack)
    {
        if (stack->integer < node->integer 
            && (closest_smaller == NULL || stack->integer > closest_smaller->integer))
        {
            closest_smaller = stack;
        }
        stack = stack->next;
    }
    return closest_smaller;
}

t_ps *ft_get_closest_bigger(t_ps *node, t_ps *stack)
{
    t_ps    *closest_bigger;
    
    closest_bigger = NULL;
    while (stack)
    {
        if (stack->integer > node->integer 
            && (closest_bigger == NULL || stack->integer < closest_bigger->integer))
        {
            closest_bigger = stack;
        }
        stack = stack->next;
    }
    return closest_bigger;
}
