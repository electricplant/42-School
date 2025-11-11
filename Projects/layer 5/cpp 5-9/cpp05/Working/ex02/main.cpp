/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:13:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/11 13:59:36 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "iostream"

int main(void)
{
	try // Enough to sign
	{
		Bureaucrat person1("Sarah", 145);
		ShrubberyCreationForm Bushes("Home");
		person1.signForm(Bushes);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // NOT Enough to sign
	{
		Bureaucrat person1("Sarah", 146);
		ShrubberyCreationForm Bushes("Home");
		person1.signForm(Bushes);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // Enough to execute
	{
		Bureaucrat person1("Sarah", 137);
		ShrubberyCreationForm Bushes("Home");
		person1.executeForm(Bushes);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // NOT Enough to execute
	{
		Bureaucrat person1("Sarah", 138);
		ShrubberyCreationForm Bushes("Home");
		person1.executeForm(Bushes);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

//		ROBOTOMY FORM    ////////////////////////////////////////////////////////////////////////

	try // Enough to sign
	{
		Bureaucrat person2("Farnsworth", 72);
		RobotomyRequestForm Robotize("Bender");
		person2.signForm(Robotize);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // NOT Enough to sign
	{
		Bureaucrat person2("Farnsworth", 73);
		RobotomyRequestForm Robotize("Bender");
		person2.signForm(Robotize);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // Enough to execute
	{
		Bureaucrat person2("Farnsworth", 45);
		RobotomyRequestForm Robotize("Bender");
		person2.executeForm(Robotize);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // NOT Enough to execute
	{
		Bureaucrat person2("Farnsworth", 46);
		RobotomyRequestForm Robotize("Bender");
		person2.executeForm(Robotize);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

//		PARDON FORM    ////////////////////////////////////////////////////////////////////////

	try // Enough to sign
	{
		Bureaucrat person3("Arthur", 25);
		PresidentialPardonForm Pardon("Trillian");
		person3.signForm(Pardon);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // NOT Enough to sign
	{
		Bureaucrat person3("Arthur", 26);
		PresidentialPardonForm Pardon("Trillian");
		person3.signForm(Pardon);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // Enough to execute
	{
		Bureaucrat person3("Arthur", 5);
		PresidentialPardonForm Pardon("Trillian");
		person3.executeForm(Pardon);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(AForm::FileErrorException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;

	try // NOT Enough to execute
	{
		Bureaucrat person3("Arthur", 6);
		PresidentialPardonForm Pardon("Trillian");
		person3.executeForm(Pardon);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(AForm::FileErrorException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
	std::cout << std::endl;
	
	// try
	// {
	// 	Bureaucrat person2("Bane", 0); //too high initialization
	// }
	// catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	// catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	// catch(std::exception& e) {std::cout << e.what() << std::endl;}

	// try
	// {
	// 	Bureaucrat person3("Bane 2", 150); //too low decrement
	// 	person3.decrementGrade();
	// }
	// catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	// catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	// catch(std::exception& e) {std::cout << e.what() << std::endl;}

	// try
	// {
	// 	Bureaucrat person4("Niel", 1); //too high increment
	// 	person4.incrementGrade();
	// }
	// catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	// catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	// catch(std::exception& e) {std::cout << e.what() << std::endl;}	
}