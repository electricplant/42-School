/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 06:25:37 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/07 08:34:16 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class ClassName // ( : public inheritedClassName )
{
	public: /*Access level: anyone*/

	protected: /*Access level: self and derived classes*/
	
	private: /*Access level: self only*/
		//put data here usually

	ClassName(); //default constructor
	/*explicit*/ ClassName(/*input*/); //constructor with one input (added explicit to prevent implicit(automatitc) type conversion)
	ClassName(const ClassName& other); //copy constructor
	ClassName& operator=(const ClassName& other); //assignment operator
	~ClassName();


	//types of Methods(Member functions)

		//Basic method
		void B_Example(/*input*/) {};
		//Uses: Setters, updaters,..

		//Const method - cannot modify class members (left side for return, right side for Method attribute)
		void C_Example(/*input*/) const {};
		//Uses: Getters,..

		//Static method - Access level: self only
		static void S_Example(/*input*/) {};
		//Uses: Printers,..

		//Static method - Access level: self and derived classes (can be overridden (derived class has Method with same name))
		virtual void V_Example(/*input*/) {};
		//Uses: Printers,..

	//nested class
		class InnerClassName {};
			//blah
				//to use this outside (eg. in main) do ClassName::Innerclassname

	//nested exception class
		class InnerExceptionClassName {};

};

#include <string> //for below ostream

std::ostream& operator<<(std::ostream& os, const ClassName& classname);