/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:07:49 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/11 14:13:50 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
	private:
		std::string target;
		RobotomyRequestForm();

	public:
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(const RobotomyRequestForm& other);
		RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
		~RobotomyRequestForm();

		void execute(Bureaucrat const& executor) const;
};