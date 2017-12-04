/**
	@file 		Contact.h
	@author		kmurphy
	@practical 	
	@brief		Specification of class representing a contact between two objects.
	*/

#ifndef PARTICLE_CONTACT_H
#define PARTICLE_CONTACT_H

#include "../Particle.h"

namespace YAMPE { namespace P {


class Contact: public Printable {

public:

	typedef ofPtr<Contact> Ref;

	Contact(const String label="Contact") : Printable(label) {};

	const String toString() const;
	
	Particle::Ref a;				///< Particle a involved in the contact
	Particle::Ref b;				///< Particle b, may be NULL to represent scenery.
	
	float restitution;				///< The normal restitution coefficient at the contact.
	ofVec3f contactNormal;			///< Direction of the contact in world coordinates.
	float penetration;				///< Depth of penetration at the contact.
	ofVec3f aMovement;				///< Amount of particle a is moved by during interpenetration resolution. 
	ofVec3f bMovement;				///< Amount of particle b is moved by during interpenetration resolution. 
	
	void resolve(float dt);			///< Resolves this contact, for both velocity and interpenetration.
	float calculateSeparatingVelocity() const;	///< Calculates the separating velocity at this contact.

	void resolveVelocity(float dt);	///< Handles the impulse calculations for this collision.
	void resolveInterpenetration(float dt);	///< Handles the interpenetration resolution for this contact.
};

} }
#endif