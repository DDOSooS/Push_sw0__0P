/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/30 07:36:53 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    ft_set_up_node(t_ps *cheapest, t_ps *target, t_ps **a, t_ps **b)
{
    int n_rep;

    cheapest->midpoint = ft_chek_mid_point(cheapest, *a);
    target->midpoint = ft_chek_mid_point(target, *b);
    cheapest->cost = ft_calculate_cost(cheapest, *a);
    target->cost = ft_calculate_cost(target, *b);
    n_rep = ft_min(cheapest->cost, target->cost);
    if (cheapest->midpoint && target->midpoint && cheapest->cost && target->cost)
    {
        while (n_rep--)
            ft_rrr(a, b, 1);
    }
    else if (!cheapest->midpoint &&!target->midpoint && cheapest->cost && target->cost)
        while (n_rep--)
            ft_rr(a, b, 1);                
    ft_finish_exec(cheapest, target, a, b);
}

void    ft_push_back(t_ps **a, t_ps **b)
{
    t_ps    *target;
    int     n_rep;
    
    target = ft_get_target(*b , *a , 1);
    target->midpoint = ft_chek_mid_point(target, *a);
    n_rep = ft_calculate_cost(target , *a);
    if (target->midpoint)
    {
        while (n_rep--)
            ft_rra(a, 1);
    }
    else
        while (n_rep--)
            ft_ra(a ,1);
    ft_pa(a , b, 1);
}

void    ft_bring_min(t_ps **stack)
{
    t_ps *t_min;
    int     n_rep;

    t_min = ft_get_min(*stack);
    t_min->midpoint = ft_chek_mid_point(t_min, *stack);
    n_rep = ft_calculate_cost(t_min, *stack);
    if (t_min->midpoint)
    {
        while (n_rep--)
            ft_rra(stack, 1);
    }
    else
    {
        while (n_rep--)
            ft_ra(stack, 1);
    }
}

void    ft_push_swap(t_ps **a, t_ps **b)
{
    int len_a;
    t_ps *cheapest;
    t_ps *target;
    
    len_a = ft_stack_len(*a);
    if (len_a > 4)
    {
        ft_pb(a, b , 1);
        ft_pb(a, b , 1);
    }
    else if (len_a == 4)
        ft_pb(a, b , 1);
    while (ft_stack_len(*a) > 3)
    {
        // printf("\n==================before===============\n");
        // var_dump_stack(*a, 'a');
        // var_dump_stack(*b, 'b');
        // printf("\n================================\n");
        cheapest = ft_search_cheapest(*a, *b);
        target = ft_get_target(cheapest , *b, 0);
        ft_set_up_node(cheapest, target, a, b);
        ft_pb(a, b, 1);
        // printf("\n==================after===============\n");
        // var_dump_stack(*a, 'a');
        // var_dump_stack(*b, 'b');
        // printf("\n================================\n");
    }
    ft_sort_three(a);
    while (ft_stack_len(*b))
        ft_push_back(a, b);
    ft_bring_min(a);
}

int main(int ac, char **av)
{
    t_ps    *stack_a;
    t_ps    *stack_b;

    if (ac == 1)
        return (0);
    stack_b = NULL;
    stack_a = ft_parse_args(ac , av);
    if(! stack_a)
    {
        write(2, "error\n", 6);
        return (1);
    }
    // printf("\n==================before===============\n");
    // var_dump_stack(stack_b, 'b');
    // var_dump_stack(stack_a, 'a');
    // printf("\n================================\n");
    if (!ft_is_sorted(stack_a))
        ft_push_swap(&stack_a, &stack_b);
    // printf("\n=================after===============\n");
    // var_dump_stack(stack_a, 'a');
    // var_dump_stack(stack_b, 'b');
    // printf("\n================================\n");
    // if (! ft_is_sorted(stack_a))
    //     printf("\n========> DM NOT SORTED ;( <========\n");
    ft_free_stack(&stack_a);
    ft_free_stack(&stack_b);
    return (0);
}