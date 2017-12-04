/**
	@file 		P_Contact.cpp
	@author		kmurphy
	@practical 	
	@brief		Implementation of class representing a contact between two Particles.
	*/

#include "Contact.h"

namespace YAMPE { namespace P {
	
const String Contact::toString() const {
	std::ostringstream outs;
	outs <<"Particle a = " <<a->label() <<"    "
	<<"Particle b  = " << (b==NULL ? "NULL" : b->label()) <<"    "
	<<"Restitution = " <<restitution <<"    "
	<<"Contact Normal = " <<contactNormal <<"    "
	<<"Penetration = " <<penetration <<"    "
	<<"Particle a movement = " <<aMovement <<"    "
	<<"Particle b movement = " <<bMovement <<"    ";
	return outs.str();
}

void Contact::resolve(float dt) {
	resolveVelocity(dt);
	resolveInterpenetration(dt);
}

float Contact::calculateSeparatingVelocity() const {
    ofVec3f relativeVelocity = a->velocity;
    if (b!=NULL) relativeVelocity -= b->velocity;
    return relativeVelocity.dot(contactNormal);
}

void Contact::resolveVelocity(float dt)
{
    // Find the velocity in the direction of the contact
    float separatingVelocity = calculateSeparatingVelocity();
	
    // Check if it needs to be resolved
    if (separatingVelocity > 0) {
        // The contact is either separating, or stationary - there's
        // no impulse required.
        return;
    }
	
    // Calculate the new separating velocity
    float newSepVelocity = -separatingVelocity * restitution;
	
    // Check the velocity build-up due to acceleration only
    ofVec3f accCausedVelocity = a->acceleration;
    if (b!=NULL) accCausedVelocity -= b->acceleration;
    float accCausedSepVelocity = dt * accCausedVelocity.dot(contactNormal);
	
    // If we've got a closing velocity due to acelleration build-up,
    // remove it from the new separating velocity
    if (accCausedSepVelocity < 0) {
        newSepVelocity += restitution * accCausedSepVelocity;
		
        // Make sure we haven't removed more than was there to remove
        if (newSepVelocity < 0) newSepVelocity = 0;
    }

    float deltaVelocity = newSepVelocity - separatingVelocity;
	
    // We apply the change in velocity to each object in proportion to
    // their inverse mass (i.e. those with lower inverse mass [higher
    // actual mass] get less change in velocity)..
    float totalInverseMass = a->inverseMass();
    if (b!=NULL) totalInverseMass += b->inverseMass();
	
    // If all particles have infinite mass, then impulses have no effect
    if (totalInverseMass <= 0) return;
	
    // Calculate the impulse to apply
    float impulse = deltaVelocity / totalInverseMass;
	
    // Find the amount of impulse per unit of inverse mass
    ofVec3f impulsePerIMass = contactNormal * impulse;
	
    // Apply impulses: they are applied in the direction of the contact,
    // and are proportional to the inverse mass
    a->velocity += impulsePerIMass * a->inverseMass();

	// Particle b goes in the opposite direction
	if (b!=NULL) {
		b->velocity -= impulsePerIMass * b->inverseMass();
    }
}

void Contact::resolveInterpenetration(float dt) {
	(void) dt;
	
    // If we don't have any penetration, skip this step.
    if (penetration <= 0.0f) return;
	
	// The movement of each object is based on their inverse mass, so 
	// total that.
    float totalInverseMass = a->inverseMass();
    if (b!=NULL) totalInverseMass += b->inverseMass();
	
    // If all particles have infinite mass, then we do nothing
    if (totalInverseMass <= 0.0f) return;
	
    // Find the amount of penetration resolution per unit of inverse mass
    ofVec3f movePerIMass = contactNormal * (penetration / totalInverseMass);
	
	// Calculate the the movement amounts
	aMovement = movePerIMass * a->inverseMass();
	if (b!=NULL) {
		bMovement = -movePerIMass * b->inverseMass();
	} else {
		bMovement = ofVec3f::zero();
	}
	
    // Apply the penetration resolution
    a->position += aMovement;
    if (b!=NULL) {
        b->position += bMovement;
    }
}

} }	// namespace YAMPE::P
