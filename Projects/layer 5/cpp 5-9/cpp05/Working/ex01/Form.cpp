/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:33:59 by dgerhard          #+#    #+#             */
/*   Updated: 2025/08/05 09:34:37 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

Form::Form() : name("bob"), sign(false), gradeSign(1), gradeEx(1)
{
	std::cout << "Default constructor Form called" << std::endl;
}

Form::Form(std::string name, const int gradeSign, const int gradeEx)
	: name(name), gradeSign(gradeSign), gradeEx(gradeEx)
{}


Form::Form(const Form& other)
	: name(other.name), sign(other.sign), gradeSign(other.gradeSign), gradeEx(other.gradeEx)
{
	std::cout << "Copy constructor called" << std::endl;
}

Form& Form::operator=(const Form& other)
{
	if (this != &other)
		sign = other.sign;
	return *this;
}

Form::~Form()
{
	std::cout << "Default destructor Form called" << std::endl;
}

std::string Form::getName() const
{
	return this->name;
}

bool Form::getSign() const
{
	return this->sign;
}

int Form::getGradeSign() const
{
	return this->gradeSign;
}

int Form::getGradeEx() const
{
	return this->gradeEx;
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() <= this->gradeSign)
	{
		this->sign = true;
	}
	else
	{
		throw Form::GradeTooLowException();
	}
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Form Grade too low!";
}

const char* Form::GradeTooHighException::what() const throw()
{
    return "Form Grade too high!";
}


std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << form.getName() << ", bureaucrat gradeSign" << form.getGradeSign();
	return os;
}