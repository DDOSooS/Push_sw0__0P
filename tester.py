import random
import subprocess

def generate_unique_numbers(n, lower_bound, upper_bound):
    if n > (upper_bound - lower_bound + 1):
        print("Error: Cannot generate more unique numbers than available within the specified bounds.")
        return []

    unique_numbers = set()
    while len(unique_numbers) < n:
        unique_numbers.add(random.randint(lower_bound, upper_bound))

    return list(unique_numbers)

def test_program(num_tests):
    n = 500  # Number of unique random numbers to generate
    lower_bound = -2147483648  # Lower bound of the range
    upper_bound = 2147483647
    total_moves = 0
    for _ in range(num_tests):
        unique_numbers = generate_unique_numbers(n, lower_bound, upper_bound)
        numbers_string = ' '.join(map(str, unique_numbers))

        # Run your program with the generated numbers
        command = f"./push_swap {numbers_string} | wc -l"
        try:
            result = subprocess.run(command, shell=True, capture_output=True, text=True, check=True)
            moves = int(result.stdout.strip())
            total_moves += moves
            print(f"Test {num_tests}: {moves} moves")
        except subprocess.CalledProcessError as e:
            print("Test failed. Returned non-zero exit status:", e.returncode)
            print("Output:", e.output)

    average_moves = total_moves / num_tests
    print(f"\nAverage number of moves over {num_tests} tests: {average_moves}")

if __name__ == "__main__":
    num_tests = 200  # Number of tests to run
    test_program(num_tests)
