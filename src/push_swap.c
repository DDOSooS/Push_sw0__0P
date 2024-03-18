/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/17 23:53:18 by aghegrho         ###   ########.fr       */
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
    new->pa = 0;
    new->pb = 0;
    new->rrb = 0;
    new->rrb = 0;
    new->next = NULL;
    // new->prev = NULL;
    return (new);
}

int ft_push_back(t_ps   **stack, int number)
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

void    ft_free_stack(t_ps *stack)
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

int ft_check_number_bounds(long number)
{
    if (number > INT_MAX || number < INT_MIN)
        return (0);
    return (1);
}

t_ps    *ft_gen_stack_a(char **args)
{
    t_ps    *stack;
    long      number;
    int     i;

    stack = NULL;
    i = -1;
    while (args[++i])
    {
        if ( !ft_strlen(args[i])  || !ft_check_number(args[i]))
        {
            ft_free_stack(stack);
            return (NULL);
        }
        number = ft_atol(args[i]);
        if (! ft_check_number_bounds(number) || !ft_push_back(&stack, number))
        {
            ft_free_stack(stack);
            return (NULL);  
        }
    }
    return (stack);
}

void    ft_push_stack_back(t_ps **stack, t_ps *nested)
{
    t_ps    *t_tmp;
    if (!*stack)
    {
        *stack = nested;
        return ;
    }
    t_tmp = *stack;
    while (t_tmp->next)
        t_tmp = t_tmp->next;
    t_tmp->next = nested;
    // nested->prev = t_tmp;
}

// void    var_dump(char **str)
// {
//     printf("\n");
//     while (*str)
//     {
//         printf("======>(%s)<==",*str);
//         *str++;
//     }
//     printf("\n");
// }

int    ft_parse_arg(t_ps **stack_a, char *av)
{
    char    **args;
    t_ps    *tmp;
    
    args = ft_split(av);
    if (!args)
    {
        ft_free_stack(*stack_a);
        return (0);    
    }
    // var_dump(args);
    tmp = ft_gen_stack_a(args);
    ft_free_mem(args);
    if (! tmp)
    {
        ft_free_stack(*stack_a);
        return (0);
    }
    ft_push_stack_back(stack_a, tmp);
    if(! ft_parse_stack(*stack_a))
    {
        ft_free_stack(*stack_a);
        return (0);
    }
    return (1);
}

t_ps    *ft_parse_args(int ac, char **av)
{
    t_ps    *stack_a;
    int     i;

    i = 1;
    stack_a = NULL;
    while (i < ac)
    {
        if (!ft_parse_arg(&stack_a, av[i]))
        {
            printf("\n===FAILED===\n");
            return (NULL);
        }
        i++;
    }
    return  (stack_a);
}

int ft_error()
{
    write(2, "Error\n", 6);
    return (1);
}

int ft_stack_size(t_ps  *stack)
{
    int counter;

    counter = 0;
    while (stack)
    {
        counter++;
        stack = stack->next;
    }
    return (counter);
}

int ft_is_sorted(t_ps *stack)
{
    t_ps    *cur;
    t_ps    *prev;

    cur = stack->next;
    prev = stack; 
    while (cur)
    {
        if (prev->integer > cur->integer)
            return (0);
        cur = cur->next;
        prev = prev->next;
    }
    return (1);
}

// void    ft_push_swap(t_ps **stack_a, t_ps **stack_b)
// {
//     if (ft_is_sorted(*stack_a))
//     {
//         printf("\n===stack a is sorted :)====\n\n");
//         return ;
//     }
//     // ft_pb(stack_a, stack_b);
//     // ft_pb(stack_a, stack_b);
// }

int ft_strcmp(char *str , char *cmp)
{
    int     i;

    i = 0;
    while (str[i] && cmp[i] && str[i] == cmp[i])
        i++;
    return (str[i] - cmp[i]);
}

t_ps    *ft_last_element(t_ps *stack)
{
    if (!stack)
        return (NULL);
    while (stack->next)
        stack = stack->next;
    return (stack);  
}

void    ft_sa(t_ps **stack_a)
{
    t_ps    *t_tmp;
    t_ps    *t_tmp1;
    
    t_tmp = (*stack_a)->next;
    t_tmp1 = *stack_a;
    t_tmp1->next = t_tmp->next;
    t_tmp->next = t_tmp1;
    *stack_a = t_tmp;
    write(1, "sa\n", 3);
}

void    ft_sb(t_ps **stack_b)
{
    t_ps    *t_tmp;
    t_ps    *t_tmp1;
    
    t_tmp = (*stack_b)->next;
    t_tmp1 = *stack_b;
    t_tmp1->next = t_tmp->next;
    t_tmp->next = t_tmp1;
    *stack_b = t_tmp;
    write(1, "sb\n", 3);
}

void    ft_ss(t_ps *stack_a, t_ps *stack_b)
{
    ft_sa(stack_a);
    ft_sb(stack_b);
    write(1, "ss\n", 3);
}


int ft_is_operation(char *instruction)
{
    char    *operation;
    char    **args;
    int     i;

    i = 0;
    operation = "sa sb ss pa pb ra rb rr rra rrb rrr";
    args = ft_split(operation);
    if (! args)
        return (0);
    while (args[i])
    {
        if (! ft_strcmp(instruction, args[i]))
        {
            ft_free_mem(args);
            return (1);
        }
        i++;
    }
    ft_free_mem(args);
    return (0);
}

void	ft_rra(t_ps **stack_a)
{
	t_ps	*t_tmp;
	t_ps	*t_tmp1;
	
	t_tmp1 = *stack_a;
	t_tmp = ft_last_element(*stack_a);
	while (t_tmp1->next->next)
		t_tmp = t_tmp1->next;
	t_tmp1->next = NULL;
	t_tmp->next = t_tmp1;
	*stack_a = t_tmp1;
    write(1, "rra\n", 4);
}

void	ft_rrb(t_ps **stack_b)
{
	t_ps	*t_tmp;
	t_ps	*t_tmp1;
	
	t_tmp1 = *stack_b;
	t_tmp = ft_last_element(*stack_b);
	while (t_tmp1->next->next)
		t_tmp = t_tmp1->next;
	t_tmp1->next = NULL;
	t_tmp->next = t_tmp1;
	*stack_b = t_tmp1;
    write(1, "rrb\n", 4);
}

void    ft_pb(t_ps **stack_a, t_ps **stack_b)
{
    t_ps    *t_tmp;

	t_tmp = *stack_a;
	*stack_a = t_tmp->next;
	t_tmp->next = *stack_b;
	*stack_b = t_tmp;
    write(1, "pb\n", 3);
}

void    ft_rrr(t_ps **stack_a, t_ps **stack_b)
{
    ft_rra(stack_a);
    ft_rrb(stack_b);
    write(1, "rrr\n", 4);
}

void    ft_pa(t_ps **stack_a, t_ps **stack_b)
{
    t_ps    *t_tmp;

	t_tmp = *stack_b;
	*stack_b = t_tmp->next;
	t_tmp->next = *stack_a;
	*stack_a = t_tmp;
    write(1, "pa\n", 3);
}
void    ft_run_instruction_helper(char *instruction, t_ps **stack_a, t_ps **stack_b)
{
    if (!ft_strcmp(instruction, "rra"))
        ft_rra(stack_a);
    else if (!ft_strcmp(instruction, "rrb"))
        ft_rrb(stack_a);
    else if (!ft_strcmp(instruction, "rrr"))
        ft_rrr(stack_a, stack_b);    
}

int    ft_run_instruction(char *instruction, t_ps **stack_a, t_ps **stack_b)
{
    if (! ft_is_operation(instruction))
        return (0);
    if (!ft_strcmp(instruction, "sa"))
        ft_sa(stack_a);
    else if (!ft_strcmp(instruction, "sb"))
        ft_sb(stack_a);
    else if (!ft_strcmp(instruction, "ss"))
        ft_ss(stack_a, stack_b);
    else if (!ft_strcmp(instruction, "pa"))
        ft_pa(stack_a, stack_b);
    else if (!ft_strcmp(instruction, "pa"))
        ft_pa(stack_a, stack_b);
    else if (!ft_strcmp(instruction, "pb"))
        ft_pb(stack_a, stack_b);
    else if (!ft_strcmp(instruction, "ra"))
        ft_ra(stack_a, stack_b);
    else if (!ft_strcmp(instruction, "rb"))
        ft_rb(stack_a, stack_b);
    else if (!ft_strcmp(instruction, "rr"))
        ft_rr(stack_a, stack_b);
    else
        ft_run_instruction_helper(instruction, stack_a, stack_b);
    return (1);
}

int    ft_repeat(char *instruction, int n_rep,t_ps **stack_a, t_ps **stack_b)
{
    int i;

    i = 0;
    while (i < n_rep)
    {
        if (!ft_run_instruction(instruction, stack_a, stack_b))
            return (0);
        i++;
    }
    return (1);
}

void    ft_sort_stack_b(t_ps **stack_b)
{
    if (ft_stack_size(*stack_b) == 2 && ! ft_is_sorted(*stack_b))
        ft_sp(stack_b);
}

int ft_get_position(t_ps *node, t_ps *stack)
{
    int position;

    position = 0;
    while (stack)
    {
        if (node->integer == stack->integer)
            return (position);
        stack = stack->next;
        position++;
    }
    return (position);
}

int ft_count_current_moves(t_ps **node, t_ps *stack_a)
{
    int moves;
    int position;
    int size;

    size = ft_stack_size(stack_a) / 2;
    moves = 0;
    position = 1;
    position = ft_get_position(*node, stack_a);
    if (position > size)   
    {
        (*node)->ra = position;
        (*node)->pb = 1;
        moves = position + 1;          
    }
    else
    {
        (*node)->rra = size - position;
        (*node)->pb = 1;
        moves = size - position + 1;
    }
    return (moves);
}

int ft_count_target_moves(t_ps *target, t_ps *stack_b)
{
    int moves;
    int position;
    int size;

    if (target->integer == (stack_b->next->integer))
        return (1);
    else
    {
        size = ft_stack_size(stack_b);
        position = ft_get_position(target, stack_b);
        if (position > (size / 2) + 1)
            moves = size - position + 1;
        else
            moves = position;
    }
    return (moves);
}

t_ps    *ft_get_target(int number, t_ps *stack_b)
{
    t_ps    *target;
    int     dif;

    target = NULL;
    dif = 0;
    while (stack_b)
    {
        if (stack_b->integer < number)
        {
            if(dif)
                dif = number - stack_b->integer;
            else
                dif = number - stack_b->integer;
            if (dif > number - stack_b->integer)
                target = stack_b;
        }
        stack_b = stack_b->next;
    }
    return(target);
}

int ft_count_cost(t_ps  **node, t_ps *stack_b, t_ps *stack_a)
{
    int     cost;
    t_ps    *target;

    cost = 0;
    target = ft_get_target((*node)->integer, stack_b);
    cost = ft_count_target_moves(target, stack_b);
    cost += ft_count_current_moves(node, stack_a);
    return (cost);
}

t_ps    *ft_get_cheap_cost(t_ps *stack_a, t_ps *stack_b)
{
    t_ps    *cheap;
    int     cost;
    t_ps    *tmp;

    tmp = stack_a;
    cheap = stack_a;
    cheap->cost = ft_count_cost(&cheap, stack_b, tmp);
    while (stack_a)
    {
        if (cheap->integer != stack_a->integer)
        {
            cost = ft_count_cost(&stack_a, stack_b, tmp);
            if (cost > cheap->cost)
            cheap = stack_a;
        }
        stack_a = stack_a->next;
    }
    return (cheap);
}


void    ft_set_up_node(t_ps *t_tmp, t_ps **stack_a, t_ps **stack_b)
{
    if (t_tmp->ra)
        ft_repeat("ra",t_tmp->ra, stack_a, stack_b);
    if (t_tmp->rra)
        ft_repeat("rb",t_tmp->rb, stack_a, stack_b);
    if (t_tmp->rra)
        ft_repeat("rrb",t_tmp->rrb, stack_a, stack_b);
    if (t_tmp->rra)
        ft_repeat("rra",t_tmp->rra, stack_a, stack_b);
    if (t_tmp->rra)
        ft_repeat("pa",t_tmp->pa, stack_a, stack_b);   
    if (t_tmp->rra)
        ft_repeat("pb",t_tmp->pb, stack_a, stack_b);
    if (t_tmp->sb)
        ft_repeat("sb",t_tmp->sb, stack_a, stack_b);
    if (t_tmp->sa)
        ft_repeat("sa",t_tmp->pa, stack_a, stack_b); 
}

int ft_get_max_position(t_ps *stack)
{
    t_ps    *t_tmp;
    t_tmp = stack;
    
    stack = stack->next;
    while (stack)
    {
        if (stack->integer > t_tmp->integer)
            t_tmp = stack; 
        stack = stack->next;   
    }
    return (ft_get_position(t_tmp, stack));
}

int ft_get_min_position(t_ps *stack)
{
    t_ps    *t_tmp;
    t_tmp = stack;
    
    stack = stack->next;
    while (stack)
    {
        if (stack->integer < t_tmp->integer)
            t_tmp = stack; 
        stack = stack->next;   
    }
    return (ft_get_position(t_tmp, stack));
}

int ft_check_stack_status(t_ps *stack)
{
    int status;
    int min;
    int max;

    min = ft_get_min_position(stack);
    max = ft_get_max_position(stack);
    if (max  == 1 && min == 1)
        status = 5;
    else if (max == 0 && min == 2)
        status = 4;
    else if(max == 1 && min == 2)
        status = 3;
    else if (max == 0 && min == 1)
        status = 2;
    else if (max == 2 && min == 1)
        status = 1;
    return (status);
}

void    ft_sort_stack_a(t_ps **stack_a)
{
    int status;

    if ( ft_is_sorted(*stack_a))
        return ;
    status = ft_check_stack_status(*stack_a);
    if (status == 1 || status  == 4 || status == 5)
        ft_sa(stack_a);
    else if (status == 2)
        ft_ra(stack_a);
    else if (status == 3)
        ft_rra(stack_a);
    return (ft_sort_stack_a(stack_a));
}

t_ps    *ft_get_target_stack_a(t_ps *stack_a, t_ps *node)
{
    t_ps    *target;
    
    target = NULL;
    while (stack_a)
    {
        if (stack_a->integer > node->integer)
        {
            if (target)
                target = stack_a;
            else
            {
                if (stack_a->integer > target->integer)
                    target = stack_a;
                if (target->integer == node->integer + 1)
                    return (target);
            }
        }
        stack_a = stack_a->next;
    }
    return (target);
}


void    ft_bring_top(t_ps *node, t_ps **stack_a, t_ps **stack_b)
{
    int     pos;
	int		size;
    int		moves;

	pos = ft_get_position(node, *stack_a);
	size = ft_stack_size(*stack_a);
	if (pos > size / 2)
	{
		moves = size - pos + 1;
		ft_repeat("rra", moves, stack_a, stack_b);
		ft_pa(stack_a, stack_b);
		return ;
	}
	else
	{
		moves = size - 1;
		ft_repeat("ra", moves, stack_a, stack_b);
		ft_pa(stack_a, stack_b);
		return ;
	}	
}


void    ft_set_up_node_stack_a(t_ps *node, t_ps **stack_a, t_ps **stack_b)
{
    t_ps    *t_tmp;

    if ((*stack_a)->integer == node->integer)
        return (ft_pa(stack_a, stack_b));
    t_tmp = ft_last_element(*stack_a);
    if (t_tmp->integer == node->integer)
    {
        ft_pa(stack_a, stack_b);
        ft_ra(stack_a, stack_b);
        return ;
    }
    ft_bring_top(node, stack_a, stack_b);
	while (!ft_is_sorted(*stack_a))
		ft_rra(stack_a);
}

/*
    check if the node value is the max value -> push it back of this list
    check if the node value is the min value -> push it intead of the head of the list
    else
        check if the target in the top  of the list -> ra 
        check if the target in the bottom of the list -> rra
*/

void    ft_push_back_stack_a(t_ps **stack_a, t_ps **stack_b)
{
    t_ps    *t_tmp;

    while (*stack_b)
    {
        t_tmp = ft_get_target_stack_a(*stack_a, *stack_b);
        ft_set_up_node_stack_a(t_tmp, stack_a, stack_b);
        *stack_b = (*stack_a)->next;
    }
}

void    ft_push_swap(t_ps **stack_a, t_ps **stack_b)
{
    t_ps    *t_tmp;
    
    if (!*stack_b)
        ft_repeat("pb", 2, stack_a, stack_b);
    ft_sort_stack_b(stack_b);
    while (ft_stack_size(*stack_b) > 3)
    {
        t_tmp = ft_get_cheap_cost(*stack_a, *stack_b);
        ft_set_up_node(t_tmp, stack_b, stack_a);
    }
    ft_sort_stack_a(stack_a);
    ft_push_back_stack_a(stack_a, stack_b);
}

void    var_dump_stack(t_ps *stack, char c)
{
    printf("======stack-%c======\n", c);
    while (stack)
    {
        printf("==>(%d)<==\n", stack->integer);
        stack = stack->next;
    }
}

int main(int ac, char **av)
{
    t_ps    *stack_a;
    t_ps    *stack_b;

    stack_a = ft_parse_args(ac , av);
    if(! stack_a)
        return (ft_error());
    var_dump_stack(stack_a, 'a');
    var_dump_stack(stack_b, 'b'); 
    printf("\n============AFTER=================\n");
    while (!ft_is_sorted(stack_a))
        ft_push_swap(&stack_a, &stack_b);
    var_dump_stack(stack_a, 'a');
    var_dump_stack(stack_b, 'b'); 
    ft_free_stack(stack_a);
    return (0);
}