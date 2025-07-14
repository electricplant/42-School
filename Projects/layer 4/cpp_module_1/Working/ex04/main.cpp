/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:57:55 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/13 11:27:42 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

void exit_err(std::string msg)
{
	std::cout << "Error: " << msg << std::endl;
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc != 4)
		exit_err("Need 3 parameters (filename, s1, s2)");

	std::ifstream fin(argv[1]);
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	if (!fin)
		exit_err("Input file invalid");
	std::string outfname = std::string(argv[1]) + ".replace";
	std::ofstream fout(outfname.c_str());
	if (!fout)
		exit_err("Could not create output file");
	
	for (std::string line; std::getline(fin, line);)
	{
		std::string::size_type n = 0;
		while ((n = line.find(s1, n)) != std::string::npos)
		{
			line.erase(n, s1.length());
			line.insert(n, s2);
			n += s2.length();
		}
		fout << line;
		if (!fin.eof())
			fout << std::endl;
	}

	fin.close();
	fout.close();

	std::cout << "all done" << std::endl;
	
	return 0;
}