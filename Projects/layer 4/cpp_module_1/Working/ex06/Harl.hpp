/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:16:28 by dgerhard          #+#    #+#             */
/*   Updated: 2025/04/28 10:43:38 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <string>
# include <iostream>

enum Level 
{
	NONE,
	DEBUG,
	INFO,
	WARNING,
	ERROR
};

class Harl
{
	void debug( void );
	void info( void );
	void warning( void );
	void error( void );

	public:
	void complain( std::string level );
};

#endif