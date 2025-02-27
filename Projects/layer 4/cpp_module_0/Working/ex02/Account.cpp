/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:48 by dgerhard          #+#    #+#             */
/*   Updated: 2025/02/27 12:08:26 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>     // std::cout
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
//#include <chrono>       // std::chrono::system_clock

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

void Account::_displayTimestamp()
{
	time_t		now;
	struct tm	*ts;
	char		buf[80];

	now = time(NULL);
	ts = localtime(&now);
	strftime(buf, sizeof(buf), "[%Y%m%d_%H%M%S] ", ts);
	std::cout << buf;
}

int Account::checkAmount(void) const
{
	std::cout << "amount:";
	return (_amount);
}

int Account::getNbAccounts(void)
{
	std::cout << "accounts:";
	return (_nbAccounts);
}

int Account::getTotalAmount(void)
{
	std::cout << ";total:";
	return (_totalAmount);
}

int Account::getNbDeposits(void)
{
	std::cout << ";deposits:";
	return (_totalNbDeposits);
}

int Account::getNbWithdrawals(void)
{
	std::cout << ";withdrawals:";
	return (_totalNbWithdrawals);
}

void Account::displayAccountsInfos()
{
	_displayTimestamp();
	std::cout << getNbAccounts() << getTotalAmount();
	std::cout << getNbDeposits() << getNbWithdrawals() << std::endl;
}

Account::Account (int initial_deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _nbAccounts << ";amount:" << initial_deposit << ";created" << std::endl;
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	_nbDeposits = 0;
	_totalAmount += initial_deposit;
	_nbAccounts++;
}

Account::~Account ()
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
	_nbAccounts--;
	_accountIndex--;
}

void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_" << checkAmount();
	std::cout << ";deposit:" << deposit << ";amount:";
	_amount += deposit;
	_nbDeposits++;
	std::cout << _amount << ";nb_deposits:" << _nbDeposits << std::endl;
	_totalNbDeposits++;
	_totalAmount += deposit;
}

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_" << checkAmount();
	std::cout << ";withdrawal:";
	if (withdrawal < _amount)
	{
		_amount -= withdrawal;
		_totalAmount -= withdrawal;
		_nbWithdrawals++;
		_totalNbWithdrawals++;
		std::cout << withdrawal << ';' << checkAmount();
		std::cout << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
		return (true);
	}
	else
	{
		std::cout << "refused" << std::endl;
		return false;
	}
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ';' << checkAmount();
	std::cout << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
}
