/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzon <wzon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:30:07 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/30 08:14:58 by wzon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <limits.h>

typedef struct push_swap
{
	int					integer;
	int					position;
	int					cost;
	int					midpoint;
	struct push_swap	*next;
	// struct push_swap	*prev;
}	t_ps;





/*
   parsing functions
*/
long int    ft_atol( char *str);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char    **ft_split(char *str);
void    ft_free_mem(char **av);
t_ps	*ft_new_node(int number);
t_ps    *ft_last_node(t_ps *list);
void    ft_free_stack(t_ps **stack);
int		ft_add_back(t_ps   **stack, int number);
int		ft_check_number(char *number);
int		ft_parse_stack(t_ps *stack);
int		ft_parse_arg(t_ps **stack_a, char *av);
t_ps	*ft_parse_args(int ac, char **av);
t_ps	*ft_gen_stack_a(char **args);
int		ft_check_number(char *number);
int		ft_check_number_bounds(long number);
int		ft_is_degit(char c);

/*
	end of parsing function
*/

/*
	push_swap_commands
*/

void    ft_pa(t_ps **stack_a, t_ps **stack_b, int flag);
void    ft_pb(t_ps **stack_a , t_ps **stack_b, int flag);
void    ft_sa(t_ps **stack_a, int flag);
void    ft_sb(t_ps **stack_b, int flag);
void    ft_ss(t_ps **stack_a, t_ps **stack_b, int flag);
void    ft_ra(t_ps **stack_a, int flag);
void    ft_rb(t_ps **stack_b, int flag);
void    ft_rr(t_ps **stack_a, t_ps **stack_b, int flag);
void    ft_rra(t_ps **stack_a, int flag);
void    ft_rrb(t_ps **stack_b, int flag);
void    ft_rrr(t_ps **stack_a, t_ps **stack_b, int flag);

/*
	end of push_swap_commands
*/


/*
	sorting_algorithm
*/
void	ft_finish_exec(t_ps *cheapest, t_ps *target, t_ps **a, t_ps **b);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
t_ps	*ft_get_max(t_ps *stack);
t_ps	*ft_get_min(t_ps *stack);
t_ps    *ft_get_target(t_ps *node, t_ps *stack, int flag);
t_ps    *ft_search_cheapest(t_ps *a, t_ps *b);
int		ft_count_cost(t_ps *node, t_ps *a, t_ps *b);
int		ft_calculate_cost(t_ps *node, t_ps *stack);
int		ft_chek_mid_point(t_ps *node, t_ps *stack);
void    ft_sort_three(t_ps **stack);
int		ft_get_position(t_ps *node, t_ps *stack);
int		ft_stack_len(t_ps *stack);
int		ft_is_sorted(t_ps *stack);
t_ps    *ft_get_closest_bigger(t_ps *node, t_ps *stack);
t_ps    *ft_get_closest_smaller(t_ps *node, t_ps *stack);
/*
	end of sorting algo functions
*/

#endif