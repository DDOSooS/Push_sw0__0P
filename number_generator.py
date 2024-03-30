import random

def generate_unique_numbers(n, lower_bound, upper_bound):
    if n > (upper_bound - lower_bound + 1):
        print("Error: Cannot generate more unique numbers than available within the specified bounds.")
        return []

    unique_numbers = set()
    while len(unique_numbers) < n:
        unique_numbers.add(random.randint(lower_bound, upper_bound))

    return list(unique_numbers)

# Example usage:
n = 500  # Number of unique random numbers to generate
lower_bound = -1000000000  # Lower bound of the range
upper_bound = 1000000000  # Upper bound of the range

unique_numbers = generate_unique_numbers(n, lower_bound, upper_bound)
# Convert the list of numbers to a string separated by spaces
numbers_string = ' '.join(map(str, unique_numbers))
print(numbers_string)
