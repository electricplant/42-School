// Assignment name  : alpha_mirror
// Expected files   : alpha_mirror.c
// Allowed functions: write
// --------------------------------------------------------------------------------
 
// Write a program called alpha_mirror that takes a string and displays this string
// after replacing each alphabetical character by the opposite alphabetical
// character, followed by a newline.
 
// 'a' becomes 'z', 'Z' becomes 'A'
// 'd' becomes 'w', 'M' becomes 'N'
 
// and so on.
 
// Case is not changed.
 
// If the number of arguments is not 1, display only a newline.
 
// Examples:
 
// $>./alpha_mirror "abc"
// zyx
// $>./alpha_mirror "My horse is Amazing." | cat -e
// Nb slihv rh Znzarmt.$
// $>./alpha_mirror | cat -e
// $
// $>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;

	while (argv[1][i] && (argc == 2))
	{
		if ((argv[1][i] >= 'a') && (argv[1][i] <= 'z'))
			argv[1][i] = (argv[1][i] + 'a' - 25) % 25 + 'a';
		else if ((argv[1][i] >= 'A') && (argv[1][i] <= 'Z'))
			argv[1][i] = (argv[1][i] - 'A' + 26) % 26 + 'A';
		write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
}