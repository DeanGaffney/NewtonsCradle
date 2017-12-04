/**
	@file 		ContactRegistry.h
	@author		kmurphy
	@practical 	
	@brief	
	*/

#ifndef PARTICLE_CONTACT_REGISTRY_H
#define PARTICLE_CONTACT_REGISTRY_H

#include "Contact.h"

namespace YAMPE { namespace P {


class ContactRegistry: public Printable {

protected:
	unsigned m_iterationLimit;		///< number of iterations allowed.
	unsigned m_iterationUsed;		///< number of iterations used.

	typedef vector<Contact::Ref> Registry;
	Registry registry;
		
public:
	typedef ofPtr<ContactRegistry> Ref;

	ContactRegistry(unsigned iterationLimit=100, String label="ContactRegistry");
	
	const String toString() const;

	void setIterationLimit(unsigned iterationLimit) { 
		m_iterationLimit = iterationLimit;
	}		
	unsigned iterationLimit() { return m_iterationLimit; }	
	unsigned iterationUsed() { return m_iterationUsed; }
	
	void append(Contact::Ref contact);
	void resolve(float dt);
	void clear();
};

} } // namespace YAMPE P

#endif