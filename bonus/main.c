/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/29 03:36:45 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void    var_dump_stack(t_ps *stack, char c);
t_ps    *ft_get_min(t_ps *stack);
/*
    libft_functions
*/
t_ps    *ft_get_max(t_ps *stack);
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

int ft_add_back(t_ps   **stack, int number)
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

int ft_is_sorted(t_ps *stack)
{
    t_ps    *cur;

    if (! stack)
      return (0);
    cur = stack;
    while (cur->next)
    {
        if (cur->integer > cur->next->integer)
        {
            // printf("\n===> (%d) > (%d)<==\n", cur->integer , cur->next->integer);
            return (0);
        }
        cur = cur->next;
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
    if (! number[i])
        return (0);
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
            ft_free_stack(&stack);
            return (NULL);
        }
        number = ft_atol(args[i]);
        if (! ft_check_number_bounds(number) || !ft_add_back(&stack, number))
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

    if (!*stack_b)
        return ;
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


    if(!*stack_a)
        return ;
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


    if(!*stack_a || !(*stack_a)->next)
        return ;
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

    if(!*stack_b || !(*stack_b)->next)
        return ;
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
    // write(1, "ss\n", 1);
}

void    ft_ra(t_ps **stack_a, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;

    if (!*stack_a || !(*stack_a)->next)
        return ;
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

    if (!*stack_b || !(*stack_b)->next)
        return ;
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
    // write(1, "rr\n", 3);
}

void    ft_rra(t_ps **stack_a, int flag)
{
    t_ps    *t_tmp;
    t_ps    *t_stmp;


    if (!*stack_a || !(*stack_a)->next)
        return ;
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

    if (!*stack_b || !(*stack_b)->next)
        return ;
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
    // write(1, "rrr\n", 4);
}
/*
    end of valid operation
*/


void    var_dump_stack(t_ps *stack, char c)
{
    printf("\n======stack-%c======\n", c);
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

int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void ft_do_instruction(char *cmd, t_ps **a, t_ps **b)
{
    if (!ft_strcmp(cmd, "pa"))
        ft_pa(a, b, 0);
    else if (!ft_strcmp(cmd, "pb"))
        ft_pb(a, b, 0);
    else if (!ft_strcmp(cmd, "sa"))
        ft_sa(a, 0);
    else if (!ft_strcmp(cmd, "sb"))
        ft_sb(b, 0);
    else if (!ft_strcmp(cmd, "ss"))
        ft_ss(a, b);
    else if (!ft_strcmp(cmd, "ra"))
        ft_ra(a, 0);
    else if (!ft_strcmp(cmd, "rb"))
        ft_rb(b, 0);
    else if (!ft_strcmp(cmd, "rr"))
        ft_rr(a, b);
    else if (!ft_strcmp(cmd, "rra"))
        ft_rra(a, 0);
    else if (!ft_strcmp(cmd, "rrb"))
        ft_rrb(b, 0);
    else if (!ft_strcmp(cmd, "rrr"))
        ft_rrr(a, b);
}

int ft_strncmp(char *s1, char *s2, int n)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
        i++;
    return (s1[i] - s2[i]);
}

char *ft_check_cmd(char *cmd, char **cmd_list)
{
    int     i;
    int     len;
    
    i = 0;
    len = ft_strlen(cmd);
    while (cmd_list[i])
    {
        // printf("\n==> cmd (%s)| cmd_list (%s)<========= cmd _len (%d)===\n\n\n", cmd, cmd_list[i], len);
        if (ft_strncmp(cmd, cmd_list[i], len - 1) == 0)
        {
            // printf("\n====returned cmd is :%s ====\n", cmd_list[i]);
            return (cmd_list[i]);
        }
        i++;
    }
    return (NULL);
}

int    ft_checker(t_ps **a, t_ps **b)
{
    char *line;
    char **cmd_list;
    char *cmd;
    
    cmd_list = ft_split("pa pb sa sb ss ra rb rr rra rrb rrr");
    line = get_next_line(0);
    while (line)
    {
        cmd = ft_check_cmd(line , cmd_list);
        free(line);
        if (!cmd)
        {
            ft_free_mem(cmd_list);
            write(1, "Error\n", 6);
            return (0);
        }
        ft_do_instruction(cmd, a, b);
        line = get_next_line(0);
    }
    ft_free_mem(cmd_list);
    return (1);
}

int main(int ac, char **av)
{
    t_ps    *stack_a;
    t_ps    *stack_b;

    if (ac == 1)
        return (1);
    stack_b = NULL;
    stack_a = ft_parse_args(ac , av);
    if(! stack_a)
    {
        write(2, "error\n", 6);
        return (1);
    }
    if (! ft_checker(&stack_a, &stack_b))
    {
        ft_free_stack(&stack_a);
        ft_free_stack(&stack_b);
        return (1);
    }
    if (ft_is_sorted(stack_a) && ! stack_b)
        write(1, "OK\n", 3);
    else
        write(1, "KO\n", 3);
    // printf("\n=================after===============\n");
    // var_dump_stack(stack_a, 'a');
    // var_dump_stack(stack_b, 'b');
    // printf("\n================================\n");

    
    ft_free_stack(&stack_a);
    ft_free_stack(&stack_b);
    return (0);
}