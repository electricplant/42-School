/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:45:02 by dgerhard          #+#    #+#             */
/*   Updated: 2025/08/08 11:41:01 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Bureaucrat;

class AForm
{
	private:
		std::string name;
		bool sign;
		const int gradeSign;
		const int gradeEx;

	public:
		AForm();
		AForm(std::string name, const int gradeSign, const int gradeEx);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm();

		std::string getName() const;
		bool getSign() const;
		int getGradeSign() const;
		int getGradeEx() const;

		void beSigned(const Bureaucrat& bureaucrat);

		virtual void execute(Bureaucrat const& executor) const = 0;

		class GradeTooLowException: public std::exception{
			public:
				virtual const char* what() const throw();
		};
		class GradeTooHighException: public std::exception{
			public:
				virtual const char* what() const throw();
		};
		class GradeNotEnoughException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& os, const AForm& AForm);