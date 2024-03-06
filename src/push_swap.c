/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/06 21:29:30 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_parse_stack(t_ps *stack)
{
    
}

void    ft_free_stack(t_ps  *stack)
{
    t_ps    *tmp;

    if (!stack)
        return ;
    while (stack->next)
    {
        tmp = stack->next;
        free(stack);
        stack = tmp;    
    }
}

int ft_is_degit(char c)
{
    if (c >= '0' && c <='9')
        return (1);
    return (0);
}

int ft_atoi(char *number)
{
    int     i;
    int     sum;
    int     sign;

    sign = 1;
    i = 0;
    sum = 0;
    while (number[i] && (number[i] > 9 && number[i] < 12))
        i++;
    if (number[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (number[i] && (number[i] >= '0' && number[i] <= '9'))
    {
        sum = sum * 10 + (number[i] - '0');
        i++;
    }
    return (sum * sign);
}

int ft_check_number(char *number)
{
    int     i;

    
    i = 0;
    if (number[0] == '-' || number[0] == '+')
        i++;
    while (number[i])
    {
        if (!ft_is_degit(number[i]))
            return (0);
        i++;
    }
    return (1);
}

t_ps    *ft_gen_stack_a(char **args)
{
    int     integer;
    t_ps    *t_tmp;
    int     i;

    i = 0;
    while (args[i])
    {
        if (!ft_check_number(integer))
        {
            ft_free_stack(t_tmp);
            return (NULL);
        }
        integer = ft_atoi(args);
        ft_push_back(t_tmp, integer);
        i++;
    }
    return (t_tmp);
}

int ft_parse_binary_arg(char *av,t_ps **stack_a)
{
    char    **args;
    int
    args = ft_split(av);
    if (!args)
        return (0);
    *stack_a = ft_gen_stack_a(args);
    if (! *stack_a)
        return (0);
    if(! ft_parse_stack(*stack_a))
        return (0);
    return (1);
}

# include <stdio.h>
int main(int ac, char **av)
{
    t_ps    *stack_a;
    t_ps    *stack_b;
    
    // if (ac < 2)
    //     return (1);
    // if (ac == 2)
    // {
    //     if (! ft_parse_binary_arg(av[1], &stack_a))
    //         return (1);
    // }
    // else if (!ft_parse_args(ac , av))
    //     return (1);
    //     return (ft_error());
    // stack_a =ft_gen_stack_a(av[1]);
    // if (!stack_a)
    //     return (ft_error());
    // ft_push_swap(stack_a, stack_b);
    printf("\n===>%d\n",ft_atoi(av[1]));
    return (0);
}