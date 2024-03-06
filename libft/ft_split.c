/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:20:06 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/06 19:15:47 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_strlen(char *str)
{
    int i;

    i = -1;
    while (str[++i]);
    return (i);
}

void    ft_free_mem(char **av)
{
    int i;

    i = 0;
    while (av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
    av = NULL;
}

int ft_count_args(char *str , char c)
{
    int counter;
    int i;

    if (!str)
        return (0);
    i = 0;
    counter = 0;
    while (str[i])
    {
        while (str[i] && str[i] == c)
            i++;
        if (str[i])
            counter++;
        while (str[i] && str[i] != c)
            i++;
    }
    return (counter);
}

char    *ft_gen_arg(char *src, char c)
{
    int     i;
    int     len;
    char    *dest;

    
    i = 0;
    len = 0;
    while (src[len] && src[len] != c)
        len++;
    dest = (char *)malloc(sizeof(char) * (len + 1));
    if (!dest)
        return (NULL);
    while (i < len)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int ft_gen_args(char **av, char *str, char c)
{
    int     i;
    int     k;

    i = 0;
    k = 0;
    while (str[i])
    {
        while (str[i] && str[i] == c)
            i++;
        if (str[i])
        {
            av[k] = ft_gen_arg(&str[i], c);
            if (!av[k])
            {
                ft_free_mem(av);
                return (0);
            }
        }
        i += ft_strlen(av[k]);
        k++;
    }
    av[k] = NULL;
    return (1);
}

char    **ft_split(char *str)
{
    int     ac;
    char    **av;

    ac = ft_count_args(str, ' ');
    av = (char **)malloc(sizeof(char *) * (ac + 1));
    if (!av)
        return (NULL);
    if (! ft_gen_args(av, str, ' '))
        return (NULL);
    return (av);
}
