/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:33:31 by dgerhard          #+#    #+#             */
/*   Updated: 2025/05/03 10:38:45 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"
#include <iomanip>
#include <string>
#include <iostream>
#include <limits>

Contact::Contact ()
{
	for (int i = 0; i < 5; ++i)
	{
		details[i] = "";
	}
}

Contact::Contact (const std::string details_to_add[5])
{
	for (int i = 0; i < 5; ++i)
	{
		details[i] = details_to_add[i];
	}
}

PhoneBook::PhoneBook ()
{
	saved = 0;
	prompts[0] = "First Name:";
	prompts[1] = "Last Name:";
	prompts[2] = "Nickname:";
	prompts[3] = "Phone Number:";
	prompts[4] = "Darkest Secret:";
}

void	print_index_full(PhoneBook &book, int i)
{
	int k = 0;

	while (k <= 4)
	{
		std::cout << book.prompts[k] << book.contacts[i].details[k] << std::endl;
		k++;
	}
}

void	print_index(PhoneBook &book, int j)
{
	std::string str;
	std::string substr;
	int k = 0;
	int i = j - 1;

	std::cout << std::setw(10) << i << '|';
	while (k <= 2)
	{
		str = book.contacts[i].details[k];
		if (str.length() > 10)
		{
			substr = str.substr(0, 9);
			std::cout << std::setw(9) << substr << '.';
		}
		else
			std::cout << std::setw(10) << str;
		std::cout << '|';
		k++;
	}
	std::cout << std::endl;
}

void	print_book(PhoneBook &book)
{
	int i = 1;

	std::cout << std::endl;
	while (i <= book.saved)
		print_index(book, i++);
	std::cout << std::endl;
}

void search_contact(PhoneBook &book)
{
	int index = 0;

	print_book(book);
	std::cout << REQ_INPUT;
	std::cin.setf(std::ios_base::dec, std::ios_base::basefield);

	while (!(std::cin >> index)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << ERR_INPUT << std::endl << REQ_INPUT;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (index >= 0 && index < book.saved)
		print_index_full(book, index);
	else
		std::cout << ERR_INPUT << std::endl;
}

void	add_contact(PhoneBook &book)
{
	std::string	details[5];
	std::string	input;
	int	i = 0;

	while (i <= 4)
	{
		std::cout << book.prompts[i];
		getline(std::cin, input);
		if (input.empty())
			std::cout << ERR_EMPTY << std::endl;
		else
			details[i++] = input;
	}
	Contact new_contact(details);
	if (book.saved <= 7)
		book.saved++;
	book.contacts[book.saved - 1] = new_contact;
	print_index(book, book.saved);
}

void	prompt_user(PhoneBook &book)
{
	std::string	input;
	while (true)
	{
		std::cout << REQ_OPTION << std::endl;
		
		if (!std::getline(std::cin, input))
		{
			if (std::cin.eof())
			{
				std::cin.clear();
				input = "";
				std::cout << std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}
		if (input == "ADD")
			add_contact(book);
		else if (input == "SEARCH")
			search_contact(book);
		else if (input == "EXIT")
			break ;
		else
			std::cout << ERR_OPTION << std::endl;
	}
}

int	main()
{
	PhoneBook book;
	prompt_user(book);
	return (0);
}
