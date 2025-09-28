/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:33:59 by dgerhard          #+#    #+#             */
/*   Updated: 2025/08/08 11:41:58 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

AForm::AForm() : name("bob"), sign(false), gradeSign(1), gradeEx(1)
{
	// std::cout << "Default constructor AForm called" << std::endl;
}

AForm::AForm(std::string name, const int gradeSign, const int gradeEx)
	: name(name), gradeSign(gradeSign), gradeEx(gradeEx)
{}


AForm::AForm(const AForm& other)
	: name(other.name), sign(other.sign), gradeSign(other.gradeSign), gradeEx(other.gradeEx)
{
	// std::cout << "Copy constructor called" << std::endl;
}

AForm& AForm::operator=(const AForm& other)
{
	if (this != &other)
		sign = other.sign;
	return *this;
}

AForm::~AForm()
{
	// std::cout << "Default destructor AForm called" << std::endl;
}

std::string AForm::getName() const
{
	return this->name;
}

bool AForm::getSign() const
{
	return this->sign;
}

int AForm::getGradeSign() const
{
	return this->gradeSign;
}

int AForm::getGradeEx() const
{
	return this->gradeEx;
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() <= this->gradeSign)
	{
		this->sign = true;
	}
	else
	{
		throw AForm::GradeTooLowException();
	}
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "Grade too low!";
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return "Grade too high!";
}

const char* AForm::GradeNotEnoughException::what() const throw()
{
    return "Grade not high enough for this task!";
}

const char* AForm::FileErrorException::what() const throw()
{
    return "Error opening file";
}


std::ostream& operator<<(std::ostream& os, const AForm& AForm)
{
	os << AForm.getName() << ", bureaucrat gradeSign" << AForm.getGradeSign();
	return os;
}