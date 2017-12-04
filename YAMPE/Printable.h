/**
	@file 		Printable.h
	@author		kmurphy
	@practical 	
	@brief		Utility class to simplify logging of entiies in a physical simuation.
	*/

#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <iostream>
#include <sstream>

#include "util.h"

namespace YAMPE {
	
/**
	\class Printable
	
	Utility base class to simplify logging of entities in simulations.

	The class provides a text label for identification and provides a 
	Java-like toString function which is used in the overloaded 
	output stream operator.

 */

class Printable {
	
public:
	
	Printable(String label="") : m_label(label) { };
	
	Printable& setLabel(String label);
	String label() const;
	
	/// Java-like toString function for debugging/logging 
	virtual const String toString() const = 0;
	friend std::ostream& operator <<(std::ostream& outputStream, const Printable& p);
	
private:	
	String m_label;
		
};

}	// namespace YAMPE

#endif
