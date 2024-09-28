// Assignment name  : add_prime_sum
// Expected files   : add_prime_sum.c
// Allowed functions: write, exit
// --------------------------------------------------------------------------------

// Write a program that takes a positive integer as argument and displays the sum
// of all prime numbers inferior or equal to it followed by a newline.

// If the number of arguments is not 1, or the argument is not a positive number,
// just display 0 followed by a newline.

// Examples:
// $>./add_prime_sum 5
// 10
// $>./add_prime_sum 7 | cat -e
// 17$
// $>./add_prime_sum | cat -e
// 0$
// $>
#include <unistd.h>

int	ft_atoi(char *str)
{
	
}

int	is_prime(int num)
{

}

int	main(int argc, char **argv)
{
	if ((argc == 2) && (ft_atoi(argv[1]) > 0))
	{

	}
	else
		write(1, "0", 1);
	write(1, "\n", 1);
}