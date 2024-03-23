/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:20:06 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/18 22:32:45 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
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

char	*ft_gen_arg(char *str, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	ft_gen_args(char **words,char *str, char c)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			len = 0;
			while (str[i] && str[i] != c)
			{
				len++;
				i++;
			}
			// printf("\n===%d|%c==\n",len, str[i]);
			words[j] = ft_gen_arg(&str[i - len], len);
			j++;
		}
	}
	words[j] = NULL;
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

// int main()
// {
//     char *str = " akl asd;  ;ds    ";
//     char **args = ft_split(str);
//     int i ;

//     i = 0;
//     while (args[i])
//     {
//         printf("==>arg:%s<==\n",args[i]);
//         i++;
//     }
//     ft_free_mem(args);    
//     return (0);
// }