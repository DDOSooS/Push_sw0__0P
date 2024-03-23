/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/23 03:36:11 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    var_dump_stack(t_ps *stack, char c);

/*
    libft_functions
*/

t_ps    *ft_new_node(int number)
{
    t_ps    *new;

    new = malloc(sizeof(t_ps));
    if (! new)
        return (NULL);
    new->integer = number;
	new->ra = 0;
	new->rb = 0;
	new->rra = 0;
	new->rrb = 0;
    new->next = NULL;
    return (new);
}

int ft_push_back(t_ps   **stack, int number)
{
    t_ps    *tmp;
    t_ps    *new;

    new = ft_new_node(number);
    if (!new)
        return (0);
    if (! stack || ! *stack)
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

t_ps    *ft_last_node(t_ps *list)
{
    while (list->next)
        list = list->next;
    return (list);
}

int ft_is_sort(t_ps *stack)
{
    t_ps    *cur;
    t_ps    *prev;

    if (! stack)
      return (0);
    prev = stack;
    cur = stack->next;
    while (cur->next)
    {
        if (prev->integer > cur->integer)
            return (0);
        cur = cur->next;
        prev = prev->next;
    }
    return (1);
}

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

/*
    end of libft_functions
*/
/*
    parsing cmd line argument
*/

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
    {
        return (0);
    }
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
            ft_free_stack(&stack);
            return (NULL);
        }
        number = ft_atol(args[i]);
        if (! ft_check_number_bounds(number) || !ft_push_back(&stack, number))
        {
             ft_free_stack(&stack);
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

void    var_dump(char **str)
{
    printf("\n");
    int i;

    i = 0;
    while (str[i])
    {
        printf("======>(%s)<==",str[i]);
        i++;
    }
    printf("\n");
}

int    ft_parse_arg(t_ps **stack_a, char *av)
{
    char    **args;
    t_ps    *tmp;

    args = ft_split(av);
    if (!args)
    {
        ft_free_stack(stack_a);
        return (0);
    }
    // var_dump(args);
    tmp = ft_gen_stack_a(args);
    ft_free_mem(args);
    if (! tmp)
    {
         ft_free_stack(stack_a);
        return (0);
    }
    ft_push_stack_back(stack_a, tmp);
    if(! ft_parse_stack(*stack_a))
    {
         ft_free_stack(stack_a);
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
            printf("\n===failed===\n");
            return (NULL);
        }
        i++;
    }
    return  (stack_a);
}

/*
    end of parsing cmd line argument
*/


/*
    the recomonded operation of push swap
*/

void    ft_pa(t_ps **stack_a, t_ps **stack_b, int flag)
{
    t_ps    *t_tmp;

    t_tmp = *stack_b;
    *stack_b = t_tmp->next;
    t_tmp->next = *stack_a;
    *stack_a = t_tmp;
    if (flag)
        write(1, "pa\n", 3);
}

void    ft_pb(t_ps **stack_a , t_ps **stack_b, int flag)
{
    t_ps    *t_tmp;

    t_tmp = *stack_a;
    *stack_a = t_tmp->next;
    t_tmp->next = *stack_b;
    *stack_b = t_tmp;
    if (flag)
        write(1, "pb\n", 3);
}

void    ft_sa(t_ps **stack_a, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;

    t_tmp = (*stack_a);//1
    t_stmp = (*stack_a)->next;//2
    t_tmp->next = (*stack_a)->next->next;//1->3->4->5
    t_stmp->next = t_tmp;//2->1->3->4->5
    *stack_a = t_stmp;
    if (flag)
        write(1, "sa\n", 3);
}

void    ft_sb(t_ps **stack_b, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;

    t_tmp = (*stack_b);//1
    t_stmp = (*stack_b)->next;//2
    t_tmp->next = (*stack_b)->next->next;//1->3->4->5
    t_stmp->next = t_tmp;//2->1->3->4->5
    *stack_b = t_stmp;
    if (flag)
        write(1, "sb\n", 3);
}

void    ft_ss(t_ps **stack_a, t_ps **stack_b)
{
    ft_sa(stack_a, 0);
    ft_sb(stack_b, 0);
    write(1, "ss\n", 1);
}

void    ft_ra(t_ps **stack_a, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;

    t_tmp = (*stack_a)->next;
    t_stmp = ft_last_node(*stack_a);
    t_stmp->next = (*stack_a);
    t_stmp->next->next = NULL;
    *stack_a = t_tmp;
    if (flag)
        write(1, "ra\n", 3);
}

void    ft_rb(t_ps **stack_b, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;

    t_tmp = (*stack_b)->next;
    t_stmp = ft_last_node(*stack_b);
    t_stmp->next = (*stack_b);
    t_stmp->next->next = NULL;
    *stack_b = t_tmp;
    if (flag)
        write(1, "rb\n", 3);
}

void    ft_rr(t_ps **stack_a, t_ps **stack_b)
{
    ft_ra(stack_a, 0);
    ft_ra(stack_b, 0);
    write(1, "rr\n", 3);
}

void    ft_rra(t_ps **stack_a, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;

    t_tmp = *stack_a;
    t_stmp = ft_last_node(*stack_a);
    while (t_tmp->next->next)
        t_tmp = t_tmp->next;
    t_tmp->next = NULL;
    t_stmp->next = *stack_a;
    *stack_a = t_stmp;
    if (flag)
        write(1, "rra\n", 4);
}

void    ft_rrb(t_ps **stack_b, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;

    t_tmp = *stack_b;
    t_stmp = ft_last_node(*stack_b);
    while (t_tmp->next->next)
        t_tmp = t_tmp->next;
    t_tmp->next = NULL;
    t_stmp->next = *stack_b;
    *stack_b = t_stmp;
    if (flag)
        write(1, "rrb\n", 4);
}

void    ft_rrr(t_ps **stack_a, t_ps **stack_b)
{
    ft_rra(stack_a, 0);
    ft_rrb(stack_b, 0);
    write(1, "rrr\n", 1);
}
/*
    end of valid operation
*/


/*
    start of the sorting algorith
*/


/*
    @return (void)
    check the cheap cost in stack_a and push it to stack_b
    how to calculate the cheapest node ?
    it the combination of the cost of the current node and its target
    cost = curr_cost + target_cost;
    cost = how many move to the node the to top of the stack
*/

    /*
        check fot the closest begier number to the node->integer
    */


int ft_count_cost(t_ps *node, t_ps *stack)
{
    int cost;
    int position;
    int len;

    len = ft_stack_len(stack);
    position = ft_get_position(node, stack);
    if (len / 2 >= position)
		cost = position;
    else
        cost = len - position;
    return (cost);
}

int    ft_is_sort_rec(t_ps *stack)
{
    t_ps    *cur;
    t_ps    *prev;

    if (! stack)
      return (0);
    prev = stack;
    cur = stack->next;
    while (cur)
    {
        if (prev->integer < cur->integer)
            return (0);
        cur = cur->next;
        prev = prev->next;
    }
    return (1);
}

t_ps    *ft_search_cheapest(t_ps *stack_a, t_ps *stack_b)
{
    t_ps    *t_cheapest;
    t_ps    *t_tmp;

    t_tmp = stack_a;
    t_cheapest = t_tmp;
    t_cheapest->cost = ft_count_cost(t_cheapest, stack_a);
    t_tmp = t_tmp->next;
    while (t_tmp)
    {
        t_tmp->cost = ft_count_cost(t_tmp, stack_a);
        if (t_tmp->cost < t_cheapest->cost)
            t_cheapest = t_tmp;
        t_tmp = t_tmp->next;
    }
    return (t_cheapest);
}

t_ps    *ft_get_target(t_ps *node, t_ps *stack)
{
    int		dif;
	t_ps	*t_target;
	int		tmp;
	
	dif = 0;
	t_target = NULL;
	while (stack)
	{
		if (stack->integer < node->integer)
		{
			if (dif)
			{
				tmp = node->integer - stack->integer;
				if (dif > tmp)
					dif = tmp;
			}
			else
				dif = node->integer - stack->integer;
		}
		stack = stack->next;
	}
	return (t_target);
}


/*
	@ft_first_exec & ft_second_exec are function aim to optimize the number of moves
*/

void	ft_first_exec(t_ps *target_a, t_ps *target_b, t_ps **stack_a, t_ps **stack_b)
{
	int		n_rep;

	n_rep = 0;
	if (! target_a->ra && ! target_a->rb)
		return ;
	if (target_a->ra && target_b->rb)
	{
		if (target_a->ra > target_b->rb)
			n_rep = target_b->rb;
		while (n_rep--)
			ft_rr(stack_a, stack_b);
	}
	if (target_a->ra)
		while (target_a->ra--)
			ft_ra(stack_a, 1);
	if (target_b->rb)
		while (target_b->rb--)
			ft_rb(stack_b, 1);
}

void	ft_second_exec(t_ps *target_a, t_ps *target_b, t_ps **stack_a, t_ps **stack_b)
{
	int		n_rep;

	if (! target_a->rra && ! target_a->rrb)
		return ;
	n_rep = 0;
	if (target_a->rra && target_b->rrb)
	{
		if (target_a->rra > target_b->rrb)
			n_rep = target_b->rrb;
		while (n_rep--)
			ft_rrr(stack_a, stack_b);
	}
	if (target_a->rra)
		while (target_a->rra--)
			ft_rra(stack_a, 1);
	if (target_b->rrb)
		while (target_b->rrb--)
			ft_rrb(stack_b, 1);
}

void    ft_set_moves(t_ps **target, t_ps *stack, int flag)
{
    int     len;
    int     pos;

    len = ft_stack_len(stack);
    pos = ft_get_position(*target, stack);
    if (len / 2 > pos && flag)
        (*target)->ra = pos;
    else if (len / 2 > pos && !flag)
        (*target)->rb = pos;
    else if (flag)
        (*target)->rra = len - pos;
    else
        (*target)->rrb = len - pos;
}

void    ft_push_stack_b(t_ps **stack_a, t_ps **stack_b)
{
    t_ps    *target_a;
    t_ps    *target_b;

    target_a = ft_search_cheapest(*stack_a, *stack_b);
    target_b = ft_get_target(target_a, *stack_b);
	ft_set_moves(&target_a, *stack_a, 0);
	ft_set_moves(&target_b, *stack_b, 1);
	ft_first_exec(target_a, target_b, stack_a, stack_b);
	ft_second_exec(target_a, target_b, stack_a, stack_b);
}

void    ft_push_swap(t_ps **stack_a, t_ps **stack_b)
{
    if (!*stack_b)
    {
        if (ft_stack_len(*stack_a) == 4)
            ft_pb(stack_a, stack_a, 1);
        else
        {
            ft_pb(stack_a, stack_b, 1);
            ft_pb(stack_a, stack_b, 1);
        }
    }
    while (ft_stack_len(*stack_a) < 4)
        ft_push_stack_b(stack_a, stack_b);
    // ft_push_sort_three(stack_a);
    // ft_push_stack_a(stack_a, stack_b);
    // ft_sort_stack_a(stack_a);
}

/*
    end of sorting stack
*/

/*
    debuging function
*/
void    var_dump_stack(t_ps *stack, char c)
{
    printf("======stack-%c======\n", c);
    if (! stack) 
        return ;
    while (stack)
    {
        printf("==>(%d)<==\n", stack->integer);
        stack = stack->next;
    }
}
/*
    end of debuging pushing
*/

int main(int ac, char **av)
{
    t_ps    *stack_a;
    t_ps    *stack_b;
    t_ps    *t_tmp;

    stack_b = NULL;
    stack_a = ft_parse_args(ac , av);
    if(! stack_a)
    {
        write(2, "error\n", 6);
        return (1);
    }
    printf("\n==================before===============\n");
    var_dump_stack(stack_b, 'b');
    var_dump_stack(stack_a, 'a');
    printf("\n================================\n");
    if (!ft_is_sort(stack_a))
        ft_push_swap(&stack_a, &stack_b);
    printf("\n=================after===============\n");
    var_dump_stack(stack_a, 'a');
    var_dump_stack(stack_b, 'b');
    printf("\n================================\n");
    ft_free_stack(&stack_a);
    return (0);
}
