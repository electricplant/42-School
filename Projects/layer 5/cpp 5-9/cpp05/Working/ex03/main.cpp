/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:13:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/09/28 13:44:21 by dgerhard         ###   ########.fr       */
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

	try // Incorrect Form name
	{
		Intern someRandomIntern;
		AForm* rrf;

		rrf = someRandomIntern.makeForm("lobotomy request", "Bender");
		if (rrf) delete rrf;
	}
	catch(Intern::InvalidFormException& e) {std::cout << e.what() << std::endl;}

}