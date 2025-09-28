/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:07:51 by dgerhard          #+#    #+#             */
/*   Updated: 2025/09/21 12:30:08 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target)
: AForm("Robotomy", 72, 45), target(target)
{
	// std::cout << "Default constructor Robotomy called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
: AForm(other), target(other.target)
{
	// std::cout << "Copy constructor Robotomy called" << std::endl;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		target = other.target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{	
	// std::cout << "Destructor Robotomy called" << std::endl;
}

void RobotomyRequestForm::execute(Bureaucrat const& executor) const
{
	if (executor.getGrade() > 45)
		throw AForm::GradeNotEnoughException();
	
	bool fiftypercent;
	std::srand(std::time(NULL));
	fiftypercent = (rand() % 2 == 0);

	std::cout << "*WRRRRRR* *DNKDNKDNKDNK* *PAP PAP PAP* *BZZZZZ*" << this->target << std::endl;

	if (fiftypercent)
	{
		std::cout << this->target << " has been successfully robotomized" << std::endl;
	}
	else
	{
		std::cout << "Robotomy has failed for " << this->target << std::endl;
	}

}