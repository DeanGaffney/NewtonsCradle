/**
	@file 		Printable.cpp
	@author		kmurphy
	@practical 	
	@brief		Utility class to simplify logging of entiies in a physical simuation.
	*/

#include "Printable.h"

namespace YAMPE {

String Printable::label() const { return m_label; }
Printable& Printable::setLabel(String label) {
	m_label = label;
	return *this;
}

std::ostream& operator <<(std::ostream& outputStream, const Printable& p) {
	outputStream <<"[" <<p.label() <<"] \t" <<p.toString();
	return outputStream;
}

}	// namespace YAMPE
