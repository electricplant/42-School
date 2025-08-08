/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:58:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/08/08 20:34:37 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>
#include <iostream>

void Shrubbery(Bureaucrat& target)
{
	std::string filename = target.getName() + "_shrubbery";
	std::ofstream file(filename.c_str());

	
	//create file targetName_shrubbery with ascii trees inside
}
