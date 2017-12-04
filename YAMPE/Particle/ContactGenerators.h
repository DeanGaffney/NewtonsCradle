/**
	@file 		ContactGenerators.h
	@author		kmurphy
	@practical 	
	@brief	
	*/

#ifndef PARTICLE_CONTACT_GENERATOR_H
#define PARTICLE_CONTACT_GENERATOR_H

#include "../Particle.h"
#include "Contact.h"
#include "ContactRegistry.h"

namespace YAMPE { namespace P {		
	
//class Contact;
//class ContactRegistry;

/**
	Basic polymorphic interface for all particle contact generators.
 	*/
class ContactGenerator: public Printable {
	
public:
    typedef ofPtr<ContactGenerator> Ref;

	ContactGenerator(const String label="ContactGenerator") : Printable(label) {};

	/// Fills the given contact structure with the generated contact
	virtual void generate(ContactRegistry::Ref contactRegstry) = 0;
};


// --------------------------------------------------------



class GroundContactGenerator: public ContactGenerator {
public:
	ParticleRegistry particles;

	GroundContactGenerator(const String label="GroundContactGenerator") 
		: ContactGenerator(label) {};
	
	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


// --------------------------------------------------------


class ParticleParticleContactGenerator: public ContactGenerator {
public:
 	ParticleRegistry particles;

	ParticleParticleContactGenerator(const String label="ParticleParticleContactGenerator") 
		: ContactGenerator(label) {};
	
 	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


} } // namespace YAMPE P

#endif