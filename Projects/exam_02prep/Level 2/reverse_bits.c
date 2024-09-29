// ## Subject

// Assignment name  : reverse_bits
// Expected files   : reverse_bits.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write a function that takes a byte, reverses it, bit by bit (like the
// example) and returns the result.

// Your function must be declared as follows:

// unsigned char	reverse_bits(unsigned char octet);

// Example:

//   1 byte
// _____________
//  0100  0001
//      ||
//      \/
//  1000  0010

#include <unistd.h>
#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{
	int		i = 8;
	unsigned char	res = 0;

	while (i > 0)
	{
		res = res * 2 + (octet & 1);
		octet = octet / 2;
		i--;
	}
	return (res);
}

void print_binary(unsigned char octet)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", (octet >> i) & 1);
	}
	printf("\n");
}

int	main(void)
{
	unsigned char result = reverse_bits(1);
	print_binary(result);
	return 0;
}