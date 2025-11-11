/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 06:23:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/11 13:38:46 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <string>

//std::map<std::string, float> _inputDatabase;
BitcoinExchange::BitcoinExchange() { }

BitcoinExchange::BitcoinExchange(const std::string& filename)
{
	loadCsvFile();
	std::ifstream inFile(filename.c_str());
	if (!inFile.is_open())
		throw std::runtime_error("Couldn't open file: " + filename);
	loadInputFile(inFile);
	inFile.close();
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		_inputDatabase = other._inputDatabase;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange()
{
	
}

bool BitcoinExchange::_checkDate(const std::string date)
{
	if (date.length() != 10)
		return false;

	if (date[4] != '-' || date[7] != '-')
		return false;

	int year;
	int month;
	int day;
	std::istringstream yearStr(date.substr(0, 4));
	std::istringstream monthStr(date.substr(5, 2));
	std::istringstream dayStr(date.substr(8, 2));

	if (!(yearStr >> year) || !(monthStr >> month) || !(dayStr >> day))
		return false;

	if (year < 2009 || year > 2025)
		return false;
	if (month < 1 || month > 12)
		return false;

	const int daysInMonth[] = {31, 28 + (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)), 
								31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (day < 1 || day > daysInMonth[month - 1])
		return false;

	return true;
}

void BitcoinExchange::loadCsvFile()
{
	std::ifstream inFile("data.csv");
	std::string line;
	std::getline(inFile, line);
	float value;
	while (std::getline(inFile, line))
	{
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;

		std::string date = line.substr(0, commaPos);
		std::string valueStr = line.substr(commaPos + 1);

		std::istringstream iss(valueStr);
		iss >> value;
		_csvDatabase[date] = value;
	}
}

void BitcoinExchange::loadInputFile(std::ifstream& inFile)
{
	std::string line;
	while (std::getline(inFile, line))
	{
		if (line.empty())
		{
			std::cout << "Empty line\n";
		}
		size_t separatorPos = line.find(" | ");
		if (separatorPos == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;
		}
		std::string date = line.substr(0, separatorPos);
		if (!_checkDate(date))
		{
			std::cout << "Error: invalid date => " << date << "\n";
			continue;
		}
		std::string valueStr = line.substr(separatorPos + 3);

		valueStr.erase(0, valueStr.find_first_not_of(" \t"));
		valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

		std::istringstream iss(valueStr);
		float value;
		if (!(iss >> value))
		{
			std::cout << "Error: not a valid number\n";
			continue;
		}
		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: number too large." << std::endl;
			continue;
		}
		
		float rate = getExchangeRate(date);
		value *= rate;
		std::cout << date << " => " << rate << " = " << value << "\n";
		
		
	}
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
	//find exact date
	std::map<std::string, float>::const_iterator it = _csvDatabase.find(date); 
	if (it != _csvDatabase.end())
		return it->second;

	//find closest previous date
	it = _csvDatabase.lower_bound(date);
	if (it == _csvDatabase.begin() && date < it->first)
		throw std::runtime_error("Date too early");

	if (it != _csvDatabase.begin() && date < it->first)
		--it;

	return it->second;
}
