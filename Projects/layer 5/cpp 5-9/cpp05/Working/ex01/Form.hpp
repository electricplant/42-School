/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:45:02 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/11 13:54:24 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Bureaucrat;

class Form
{
	private:
		const std::string name;
		bool sign;
		const int gradeSign;
		const int gradeEx;

	public:
		Form();
		Form(std::string name, const int gradeSign, const int gradeEx);
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form();

		std::string getName() const;
		bool getSign() const;
		int getGradeSign() const;
		int getGradeEx() const;

		void beSigned(const Bureaucrat& bureaucrat);

		class GradeTooLowException: public std::exception{
			public:
				virtual const char* what() const throw();
		};
		class GradeTooHighException: public std::exception{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& os, const Form& form);