/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/21 00:11:36 by aghegrho         ###   ########.fr       */
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

t_ps    *ft_search_target(t_ps *node, t_ps  *stack)
{
    t_ps    *target;
    int     dif;

	// printf("\n======================search node==========================\n");
	var_dump_stack(stack, 'x');
	target = NULL;
    while (stack)
    {
        if (node->integer < stack->integer)
        {
            if (!dif)
            {
                target = stack;
                dif = stack->integer - target->integer;
            }
            else if (dif > stack->integer - node->integer)
            {
                target = stack;
                dif = stack->integer - node->integer;
            }
        }
        stack = stack->next;
    }
	if (target)
		printf("\n=========>> node:(%d) target:(%d)\n", node->integer, target->integer);
	// printf("\n================================================\n");
    return (target);
}

int ft_count_node_cost(t_ps *node, t_ps *stack_a, t_ps *stack_b)
{
    int     moves;
    t_ps    *target;

	// printf("\n======node (%d)=======\n", node->integer);
   	moves = 0;
	// var_dump_stack(stack_b, 'b');
	// printf("\n========end stack_b==\n");

    target = ft_search_target(node, stack_b);
	if (target)
	{
		moves = ft_count_cost(target , stack_b);
		// printf("\n=======>target moves:%d<=======\n", moves);
	}
	else
		// printf("\n>>>>>> target is NULLLLLLL <<<<<<\n");
	moves += ft_count_cost(node, stack_a);
	// printf("\n=======>cur node moves:%d<=======\n", ft_count_cost(node, stack_a));
	// printf("\n==============================================================\n");
    return (moves);
}


// void    ft_repeat_cmd(char  *instruction, t_ps **stack_a, t_ps **stack_b, int n_rep)
// {

// }

void	ft_bring_top(t_ps *node, t_ps **stack, int flag)
{
    int moves;
    int position;
    int len;

    if (! node)
        return ;
    position = ft_get_position(node , *stack);
    len = ft_stack_len(*stack);
    if (len / 2 >= position)
    {
        while (position--)
        {
            if (flag)
                ft_ra(stack, 1);
            else
                ft_rb(stack, 1);
        }
    }
    else
    {
        moves = len - position;
        while (moves--)
        {
            if (flag)
                ft_rra(stack, 1);
            else
                ft_rrb(stack, 1);
        }
    }
}

void    ft_push_stack_b(t_ps **stack_a, t_ps **stack_b)
{
    t_ps    *t_target_a;
    t_ps    *t_tmp;
    t_ps	*t_target_b;


    t_target_a = *stack_a;
    t_target_a->cost = ft_count_node_cost(t_target_a, *stack_a, *stack_b);
    t_tmp = (*stack_a)->next;
    while (t_tmp)
    {
        if (ft_count_node_cost(t_tmp, *stack_a, *stack_b) < t_target_a->cost)
            t_target_a = t_tmp;
        t_tmp = t_tmp->next;
    }
    ft_bring_top(t_target_a, stack_a, 1);
    printf("\n==> target====> (a) : (%d)<==\n", t_target_a->integer);
    var_dump_stack(*stack_b, 'x');
    t_target_b = ft_search_target(t_target_a, *stack_b);
	ft_bring_top(t_target_b, stack_b, 1);
    printf("\n===> the chosen one: (%d)<====\n", t_target_a->integer);
        printf("\n===================1=======================\n");

    // printf("\n===> the chosen one: (%d)<====\n", t_target_b->integer);
    printf("\n======================2====================\n");

    // printf("\n====> last_node (%d) target (%d) :(%d)<=====\n",ft_last_node(*stack_b)->integer,t_target_a->integer, ft_last_node(*stack_b)->integer > t_target_a->integer);
    // printf("\n==>(%d)<==\n", t_target_b->integer);
    if (t_target_b && ft_last_node(*stack_b)->integer > t_target_a->integer)
    {
        printf("\n===1===\n");
        ft_pb(stack_a, stack_b, 1);
        ft_rb(stack_b, 1);
    }
    else
    {
        printf("\n===2===\n");
        ft_pb(stack_a, stack_b, 1);
        ft_sb(stack_b, 1);
    }
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
        // printf("\n====>cur:(%d) perv:(%d)<====\n", cur->integer, prev->integer);
        if (prev->integer < cur->integer)
            return (0);
        cur = cur->next;
        prev = prev->next;
    }
    return (1);
}
void    ft_push_swap(t_ps **stack_a, t_ps **stack_b)
{
    ft_pb(stack_a, stack_b, 1);
    ft_pb(stack_a, stack_b, 1);

        // printf("\n===>(is not sorted): (%d)<===\n", ft_is_sort(*stack_b));
    if (!ft_is_sort_rec(*stack_b))
    {
        ft_sb(stack_b, 1);
        var_dump_stack(*stack_b, 'd');
    }
    var_dump_stack(*stack_a, 'a');
    var_dump_stack(*stack_b, 'b');
    while (ft_stack_len(*stack_a) > 3)
    {
        printf("\n==========================================\n");
        ft_push_stack_b(stack_a, stack_b);

        var_dump_stack(*stack_a, 'a');
        var_dump_stack(*stack_b, 'b');
    }

}


    // ft_sort_stack_a(stack_a);
    // ft_push_stack_back_a(stack_a, stack_b);
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
    // var_dump_stack(stack_b, 'b');
    // var_dump_stack(stack_a, 'a');
    if (!ft_is_sort(stack_a))
        ft_push_swap(&stack_a, &stack_b);
    var_dump_stack(stack_a, 'a');
    var_dump_stack(stack_b, 'b');

    // printf("\n==================================\n");
    // // printf("\n===>cur : (%d)  targert: (%d)<===\n", stack_a->integer , t_tmp->integer);
    // printf("\n===>cost of node (%d) is ==> (%d)<===\n", stack_a->next->integer , ft_count_node_cost(stack_a->next, stack_a, stack_b));
    ft_free_stack(&stack_a);
    return (0);
}
