/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:58:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/05 11:32:18 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
: AForm("Shrubbery", 145, 137), target(target)
{
	std::cout << "Default constructor Shrubbery called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
: AForm(other), target(other.target)
{
	std::cout << "Copy constructor Shrubbery called" << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		target = other.target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{	
	std::cout << "Destructor Shrubbery called" << std::endl;
}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const
{
	if (executor.getGrade() > 137)
		throw AForm::GradeNotEnoughException();
	std::ofstream shrubs;
	shrubs.open((this->target + "_shrubbery").c_str());
	if (!shrubs.is_open())
		throw AForm::FileErrorException();

	shrubs  << "      _/--\\ \n"
			<< "    /~     ~\\\n"
			<< " /~~    :)    ~~\\\n"
			<< "{               }\n"
			<< " \\  _-     -_  /\n"
			<< "   ~  \\\\ //  ~\n"
			<< "_- -   | | _- _\n"
			<< "  _ -  | |   -_\n"
			<< "      /   \\\n";

	shrubs.close();
	std::cout << "Made shrubs at " << this->target << std::endl;
}

