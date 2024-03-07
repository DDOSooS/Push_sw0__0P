/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/07 15:52:08 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

# include <stdio.h>
# include <limits.h>

t_ps    *ft_new_node(int number)
{
    t_ps    *new;

    new = malloc(sizeof(t_ps));
    if (! new)
        return (NULL);
    new->integer = number;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

int    ft_push_back(t_ps   **stack, int number)
{
    t_ps    *tmp;
    t_ps    *new;

    new = ft_new_node(number);
    if (!new)
        return (0);
    if (! *stack)
    {
        *stack = new;
        return (1);
    }
    tmp = *stack;
    while (tmp->next)
        tmp = tmp->next; 
    tmp->next = new;
    new->prev= tmp;
    return (1);
}

int ft_parse_stack(t_ps *stack)
{
    t_ps    *current;
    t_ps    *next_n;

    current = stack;
    while (current)
    {
        next_n = current->next;
        while (next_n)
        {
            if (current->integer == next_n->integer)
                return (0); 
            next_n = next_n->next;
        }
        current = current->next;
    }
    return (1);
}

void ft_free_stack(t_ps *stack)
{
    t_ps *tmp;

    if (!stack)
        return ;

    while (stack)
    {
        tmp = stack->next;
        free(stack);
        stack = tmp;
    }
    return ;
}

int ft_is_degit(char c)
{
    if (c >= '0' && c <='9')
        return (1);
    return (0);
}

long int    ft_atol( char *str)
{
	long res;
	int     negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	res  = res * negative;
	return res;
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

int ft_check_number_bounds(int number)
{
    if (number > INT_MAX || number < INT_MIN)
        return (0);
    return (1);
}

t_ps    *ft_gen_stack_a(char **args)
{
    t_ps    *stack;
    int     number;
    int     i;

    i = -1;
    while (args[++i])
    {
        if (! ft_check_number(args[i]))
        {
            ft_free_stack(stack);
            return (NULL);
        }
        number = ft_atol(args[i]);
        if (! ft_check_number_bounds(number) || ft_push_back(&stack, number))
        {
            ft_free_stack(stack);
            return (NULL);  
        }
    }
    return (stack);
}

t_ps    *ft_parse_binary_arg(char *av)
{
    char    **args;
    t_ps    *stack_a;
    
    args = ft_split(av);
    if (!args)
        return (NULL);
    stack_a = ft_gen_stack_a(args);
    ft_free_mem(args);
    if (! stack_a)
        return (NULL);
    if(! ft_parse_stack(stack_a))
    {
        ft_free_stack(stack_a);
        return (NULL);
    }
    return (stack_a);
}

int main(int ac, char **av)
{
    t_ps    *stack_a;
    t_ps    *stack_b;
    
    if (ac < 2)
        return (1);
    if (ac == 2)
    {
        stack_a = ft_parse_binary_arg(av[1]);
        if (!stack_a)
        {
            printf("\n======FAILED=====\n");
            return (0);
        }
        else
            printf("yes done");
    }
    ft_free_stack(stack_a);
    return (0);
}