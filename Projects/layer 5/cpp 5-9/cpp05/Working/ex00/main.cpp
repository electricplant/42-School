/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:45:39 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/11 13:52:15 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main(void)
{
	try
	{
		Bureaucrat person1("Sasha", 30); //all correct
		person1.decrementGrade();
		std::cout << person1;
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}

	std::cout << "\n";

	try
	{
		Bureaucrat person2("Bane", 0); //too high initialization
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}

	std::cout << "\n";

	try
	{
		Bureaucrat person3("Bane 2", 150); //too low decrement
		person3.decrementGrade();
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}

	std::cout << "\n";

	try
	{
		Bureaucrat person4("Niel", 1); //too high increment
		person4.incrementGrade();
		std::cout << person4;
	}
	catch(Bureaucrat::GradeTooHighException& e) {std::cout << e.what() << std::endl;}
	catch(Bureaucrat::GradeTooLowException& e) {std::cout << e.what() << std::endl;}
	catch(std::exception& e) {std::cout << e.what() << std::endl;}
}