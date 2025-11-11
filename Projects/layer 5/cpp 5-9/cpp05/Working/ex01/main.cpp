/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:45:39 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/11 13:53:46 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main(void)
{
	try
	{
		Bureaucrat person1("Sasha", 4); //all correct
		person1.incrementGrade();
		std::cout << person1 << std::endl;
		Form form1("divorce", 3, 5);
		person1.signForm(form1);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}

	std::cout << std::endl;

	try
	{
		Bureaucrat person1("Sasha", 10); //too low to sign
		person1.decrementGrade();
		std::cout << person1 << std::endl;
		Form form1("divorce", 10, 5);
		person1.signForm(form1);
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}

	std::cout << std::endl;
	
	try
	{
		Bureaucrat person2("Bane", 0); //too high initialization
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}

	std::cout << std::endl;

	try
	{
		Bureaucrat person3("Bane 2", 150); //too low decrement
		person3.decrementGrade();
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}

	std::cout << std::endl;
	
	try
	{
		Bureaucrat person4("Niel", 1); //too high increment
		person4.incrementGrade();
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
}