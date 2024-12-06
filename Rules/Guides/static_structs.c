
#include <stdio.h>
//this struct is defined at the file scope using the static keyword


static struct s_structname
{
	int a;
	char *b;

}			t_structname;

void	func(void)
{
	printf("a: %d\n", t_structname.a);
	printf("b: %s\n", t_structname.b);
}

int	main(void)
{
	t_structname.a = 42;
	t_structname.b = "Hello, World!";

	func();
	return (0);
}