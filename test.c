#include <stdio.h>
#include <stdlib.h>

// Define the t_ps structure
typedef struct t_ps {
    int data;
    struct t_ps *next;
} t_ps;

// Function to find the closest smaller element
t_ps *ft_get_closest_smaller(t_ps *node, t_ps *stack) {
    t_ps *closest_smaller = NULL;
    // Traverse the stack
    while (stack != NULL) {
        if (stack->data < node->data && (closest_smaller == NULL || stack->data > closest_smaller->data)) {
            // If the current element is smaller than the node and greater than the previous closest, update closest_smaller
            closest_smaller = stack;
        }
        stack = stack->next;
    }
    return closest_smaller;
}

// Function to create a new node
t_ps *create_node(int data) {
    t_ps *new_node = (t_ps *)malloc(sizeof(t_ps));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to free memory allocated for the linked list
void free_list(t_ps *head) {
    t_ps *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Create a sample linked list
    t_ps *head = create_node(5);
    head->next = create_node(8);
    head->next->next = create_node(3);
    head->next->next->next = create_node(6);
    head->next->next->next->next = create_node(2);

    // Choose a node
    t_ps *node = head->next->next->next->next; // Choose node with data 2

    // Find the closest smaller element
    t_ps *closest_smaller = ft_get_closest_smaller(head, head);

    // Print the result
    if (closest_smaller != NULL) {
        printf("Closest smaller element to %d is %d\n", head->data, closest_smaller->data);
    } else {
        printf("There is no smaller element than %d\n", head->data);
    }

    // Free the memory allocated for the linked list
    free_list(head);

    return 0;
}
