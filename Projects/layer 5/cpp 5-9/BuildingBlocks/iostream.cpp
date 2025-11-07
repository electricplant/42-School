/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iostream.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:20:44 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/03 09:33:49 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

int main()
{
	//when working with std::strings, you'll probably need to do stringname.c_str()

	//Basic file output
	std::ofstream outFile("test.txt");//or stringname.c_str()
	if (outFile.is_open())
	{
		outFile << "this is writing to the test.txt file" << std::endl;
		outFile.close();
	}
	else
		std::cerr << "can't open file" << std::endl;

	//File append output
	std::ofstream appendFile("test.txt", std::ios::app);
	if(appendFile.is_open())
	{
		appendFile << "Adding this line to end of test.txt" << std::endl;
		appendFile.close();
	}

	//Basic file input
	std::ifstream inFile("test.txt");
	std::string line;
	if (inFile.is_open())
	{
		while (std::getline(inFile, line))
			std::cout << line << std::endl;
		inFile.close();
	}
	else
		std::cerr << "Unable to open file for reading" << std::endl;

	














	
}