/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:46:01 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/28 20:59:26 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
void	prthat(int *arr, int *arr2);
void	move_pointer(int *array);

int	main(void)
{
	int a[] = { 1, 2, 3, 4 };
	int *b = calloc(4, sizeof(int));
	int	*a_ptr = a;
	int	*b_ptr = b;

	int i = 0;
	while (i <= 3)
	{
		b[i] = i + 2;
		i++;
	}
	prthat(a_ptr, b_ptr);
	move_pointer(a_ptr);
	prthat(a_ptr, b_ptr);
}

void	move_pointer(int *array)
{
	array++;
}

void	prthat(int *arr, int *arr2)
{
		int i = 0;

	while (i < 4)
	{
		if (arr[0] == 0 && arr2[0] == 0)
			printf("   \n");
		else if (arr[0] == 0)
			printf("  %d\n", arr2[0]);
		else if (arr2[0] == 0)
			printf("%d  \n", arr[0]);
		else
			printf("%d %d\n", arr[0], arr2[0]);
		arr++;
		arr2++;
		i++;
	}
	printf("-------\n\n");
}