/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:38:51 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/09 12:47:16 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

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
    printf("%d", 5 / 2);
    return 0;
}