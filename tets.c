/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:38:51 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/18 00:35:52 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "includes/push_swap.h"


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

int ft_strcmp(char *str , char *cmp)
{
    int     i;

    i = 0;
    while (str[i] && cmp[i] && str[i] == cmp[i])
        i++;
    return (str[i] - cmp[i]);
}

int main(int argc, char *argv[]) {
    // Check if there are any command-line arguments
    // printf("==>mine:%d<==", ft_strcmp("Aabdes","abde"));
    // printf("==>org :%d<==", strcmp("Aabdes","abde"));
    t_ps *stack;

    stack = ft_parse_args(argc , argv);
    printf("===> min index:%d <===", ft_get_min_position(stack));
    printf("%d", 5 / 2);
    return 0;
}