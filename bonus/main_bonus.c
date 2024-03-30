/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:34:45 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/30 08:13:22 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

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
        ft_ss(a, b, 0);
    else if (!ft_strcmp(cmd, "ra"))
        ft_ra(a, 0);
    else if (!ft_strcmp(cmd, "rb"))
        ft_rb(b, 0);
    else if (!ft_strcmp(cmd, "rr"))
        ft_rr(a, b, 0);
    else if (!ft_strcmp(cmd, "rra"))
        ft_rra(a, 0);
    else if (!ft_strcmp(cmd, "rrb"))
        ft_rrb(b, 0);
    else if (!ft_strcmp(cmd, "rrr"))
        ft_rrr(a, b, 0);
}

char *ft_check_cmd(char *cmd, char **cmd_list)
{
    int     i;
    int     len;
    
    i = 0;
    len = ft_strlen(cmd);
    while (cmd_list[i])
    {
        if (ft_strncmp(cmd, cmd_list[i], len - 1) == 0)
            return (cmd_list[i]);
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
        return (write(2, "error\n", 6), 1);
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
    ft_free_stack(&stack_a);
    ft_free_stack(&stack_b);
    return (0);
}
    