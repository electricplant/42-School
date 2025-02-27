/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:41:25 by dgerhard          #+#    #+#             */
/*   Updated: 2025/02/27 15:13:24 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <string>

# define ERR_EMPTY "Field can't be empty, try again"
# define REQ_INPUT "Enter Index to read:"
# define ERR_INPUT "Invalid index"
# define REQ_OPTION "PhoneBook Options: ADD, SEARCH, EXIT"
# define ERR_OPTION "Invalid option, try again"

class Contact
{
	public:
		std::string details[5];
		Contact(const std::string details_to_add[5]);

};

class PhoneBook
{
	public:
		int	saved;
		Contact contacts[8];
		std::string	prompts[5];
		PhoneBook ();
};

#endif