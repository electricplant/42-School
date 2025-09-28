/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:53:38 by dgerhard          #+#    #+#             */
/*   Updated: 2025/09/28 13:34:40 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include "AForm.hpp"

enum FormType
{
	SHRUBBERY,
	ROBOTOMY,
	PRESIDENTIAL,
	UNKNOWN
};

class Intern
{
	public:
		Intern();
		Intern(const Intern& other);
		Intern& operator=(const Intern& other);
		~Intern();

		FormType getFormType(const std::string& name);
		AForm* makeForm(std::string name, std::string target);


		class InvalidFormException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

};

std::ostream& operator<<(std::ostream& os, const Intern& Intern);