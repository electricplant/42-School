/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 09:32:05 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/19 14:48:01 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialize.hpp"
#include "Data.hpp"

int main() 
{
	Data*	data = new Data;
	uintptr_t	raw;

	std::cout << data << std::endl;

	raw = Serialize::serialize(data);

	std::cout << raw << std::endl;

	data = Serialize::deserialize(raw);

	std::cout << data << std::endl;

	delete data;
	return 0;
}