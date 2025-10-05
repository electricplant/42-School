/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:13:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/05 11:52:17 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include "iostream"

int main(void)
{
	try // Correct Form name
	{
		Intern someRandomIntern;
		AForm* rrf;

		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf) delete rrf;
	}
	catch(Intern::InvalidFormException& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // Incorrect Form name
	{
		Intern someRandomIntern;
		AForm* rrf;

		rrf = someRandomIntern.makeForm("lobotomy request", "Bender");
		if (rrf) delete rrf;
	}
	catch(Intern::InvalidFormException& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // Correct Form name and sign
	{
		Intern someRandomIntern;
		Bureaucrat Bender("Bender", 72);
		AForm* rrf;

		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf)
		{
			Bender.signForm(*rrf);
			delete rrf;
		}
	}
	catch(Intern::InvalidFormException& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // Correct Form name and not enough to sign
	{
		Intern someRandomIntern;
		Bureaucrat Leela("Leela", 73);
		AForm* rrf;

		rrf = someRandomIntern.makeForm("robotomy request", "Leela");
		if (rrf)
		{
			Leela.signForm(*rrf);
			delete rrf;
		}
	}
	catch(Intern::InvalidFormException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

}