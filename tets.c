/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghegrho < aghergho@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:38:51 by aghegrho          #+#    #+#             */
/*   Updated: 2024/03/07 13:17:50 by aghegrho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if there are any command-line arguments
    if (argc <= 1) {
        printf("No command-line arguments provided.\n");
        return 1;
    }

    // Process each argument
    for (int i = 1; i < argc; i++) {
        // Check if the argument is an empty string
        if (strlen(argv[i]) == 0) {
            printf("Error: Empty string found at position %d.\n", i);
            return 1;
        }

        // Process the argument as needed
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}