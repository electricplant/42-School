/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:53:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/11 14:16:09 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern()
{
	// std::cout << "Default Intern constructor called" << std::endl;
}
Intern::Intern(const Intern& other)
{
	// std::cout << "Copy Intern constructor called" << std::endl;
	*this = other;
}
Intern& Intern::operator=(const Intern& other)
{
	// std::cout << "Copy Intern assignment operator called" << std::endl;
	(void)other;
	return *this;
}
Intern::~Intern()
{
	// std::cout << "Default destructor called" << std::endl;
}

FormType Intern::getFormType(const std::string& name)
{
	if(name == "shrubbery creation") return SHRUBBERY;
	if(name == "robotomy request") return ROBOTOMY;
	if(name == "presidential pardon") return PRESIDENTIAL;
	return UNKNOWN;
}

AForm* Intern::makeForm(std::string name, std::string target)
{
	switch (getFormType(name))
	{
		case SHRUBBERY:
			std::cout << "Intern creates " << name << std::endl;
			return new ShrubberyCreationForm(target);
		case ROBOTOMY:
			std::cout << "Intern creates " << name << std::endl;
			return new RobotomyRequestForm(target);
		case PRESIDENTIAL:
			std::cout << "Intern creates " << name << std::endl;
			return new PresidentialPardonForm(target);
		default:
			throw InvalidFormException();
			return NULL;
	}

}

const char* Intern::InvalidFormException::what() const throw()
{
	return "Invalid Form name";
}