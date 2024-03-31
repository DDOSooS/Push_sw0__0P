/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:19:13 by wzon              #+#    #+#             */
/*   Updated: 2024/03/31 11:51:16 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

void    ft_free_stack(t_ps **stack)
{
    t_ps *tmp;

    if (!stack)
        return ;
    while (*stack)
    {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
    return ;
}

t_ps    *ft_last_node(t_ps *list)
{
    if (! list)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}

int ft_is_sorted(t_ps *stack)
{
    t_ps    *cur;
    int i;

    i = 0;
    if (! stack)
      return (0);
    cur = stack;
    while (cur->next)
    {
        if (cur->integer > cur->next->integer)
        {
            // printf("\n==> cur_node : %d | next : %d | pos : %d<===\n", cur->integer, cur->next->integer, i);
            return (0);
        }
        cur = cur->next;
        i++;
    }
    return (1);
}