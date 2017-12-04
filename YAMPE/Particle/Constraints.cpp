/**
	@file 		Constraints.cpp
	@author		kmurphy
	@practical 	
	@brief		Classes supporting various constraints between Particles.
	*/
	
#include "ContactRegistry.h"
#include "Constraints.h"

namespace YAMPE { namespace P {

// --------------------------------------------------------

float Constraint::currentLength() const {
	return (a->position-b->position).length();
}


// --------------------------------------------------------
void EqualityConstraint::generate(ContactRegistry::Ref contactRegstry) {

    // Find the current length of the constaint
    float currentLen = currentLength();

    // If constraint is satified we have noting to do here
    if (abs(currentLen-targetLength) < EPS) {
        return;
	}

    // Otherwise return the contact
    Contact::Ref contact(new Contact("EqualityConstraint"));
	contact->a = a;
    contact->b = b;

    // Calculate the normal
    ofVec3f normal = (b->position - a->position).normalized();

    // The contact normal depends on whether we're extending or compressing
    if (currentLen > targetLength) {
        contact->contactNormal = normal;
        contact->penetration = currentLen - targetLength;
    } else {
        contact->contactNormal = -normal;
        contact->penetration = targetLength - currentLen;
    }

    // Always use zero restitution (no bounciness)
    contact->restitution = 0;

	contactRegstry->append(contact);
}


const String EqualityConstraint::toString() const {
	std::ostringstream outs;
	return outs.str();
}


// --------------------------------------------------------


void MaxConstraint::generate(ContactRegistry::Ref contactRegstry) {

    // Find the current length of the constaint
    float currentLen = currentLength();

    // If constraint is satified we have noting to do here.
    if (currentLen<=targetLength) {
        return;
	}

    // Otherwise return the contact
    Contact::Ref contact(new Contact("MaxConstraint"));
	contact->a = a;
    contact->b = b;

    // Calculate the normal
    ofVec3f normal = (b->position - a->position).normalized();
    contact->contactNormal = normal;
    contact->penetration = currentLen - targetLength;

	contactRegstry->append(contact);
}


const String MaxConstraint::toString() const {
	std::ostringstream outs;
	return outs.str();
}


// --------------------------------------------------------


void MinConstraint::generate(ContactRegistry::Ref contactRegstry) {

    // Find the current length of the constaint
    float currentLen = currentLength();

    // If constraint is satified we have noting to do here.
    if (currentLen>=targetLength) {
        return;
	}

    // Otherwise return the contact
    Contact::Ref contact(new Contact("MinConstraint"));
	contact->a = a;
    contact->b = b;

    // Calculate the normal
    ofVec3f normal = (b->position - a->position).normalized();
    contact->contactNormal = -normal;
    contact->penetration =  targetLength - currentLen;

	contactRegstry->append(contact);
}


const String MinConstraint::toString() const {
	std::ostringstream outs;
	return outs.str();
}



// --------------------------------------------------------


float AnchoredConstraint::currentLength() const {
	return (a->position-anchor).length();
}


// --------------------------------------------------------
void EqualityAnchoredConstraint::generate(ContactRegistry::Ref contactRegstry) {

    // Find the current length of the constaint
    float currentLen = currentLength();

    // If constraint is satified we have noting to do here.
    if (abs(currentLen-targetLength)<1.0e-5) {
        return;
	}

    // Otherwise return the contact
    Contact::Ref contact(new Contact("EqualityAnchoredConstraint"));
	contact->a = a;
    contact->b = Particle::Ref();

    // Calculate the normal
    ofVec3f normal = (anchor - a->position).normalized();

    // The contact normal depends on whether we're extending or compressing
    if (currentLen > targetLength) {
        contact->contactNormal = normal;
        contact->penetration = currentLen - targetLength;
    } else {
        contact->contactNormal = -normal;
        contact->penetration = targetLength - currentLen;
    }

    // Always use zero restitution (no bounciness)
    contact->restitution = 0;

	contactRegstry->append(contact);
}


const String EqualityAnchoredConstraint::toString() const {
	std::ostringstream outs;
	return outs.str();
}


// --------------------------------------------------------
void MaxAnchoredConstraint::generate(ContactRegistry::Ref contactRegstry) {

    // Find the current length of the constaint
    float currentLen = currentLength();

    // If constraint is satified we have noting to do here.
    if (currentLen<=targetLength) {
        return;
	}

    // Otherwise return the contact
    Contact::Ref contact(new Contact("MaxAnchoredConstraint"));
	contact->a = a;
    contact->b = Particle::Ref();

    // Calculate the normal
    ofVec3f normal = (anchor - a->position).normalized();
    contact->contactNormal = normal;
    contact->penetration = currentLen - targetLength;

	contactRegstry->append(contact);
}


const String MaxAnchoredConstraint::toString() const {
	std::ostringstream outs;
	return outs.str();
}


// --------------------------------------------------------
void MinAnchoredConstraint::generate(ContactRegistry::Ref contactRegstry) {

    // Find the current length of the constaint
    float currentLen = currentLength();

    // If constraint is satified we have noting to do here.
    if (currentLen>=targetLength) {
        return;
	}

    // Otherwise return the contact
    Contact::Ref contact(new Contact("MinAnchoredConstraint"));
	contact->a = a;
    contact->b = Particle::Ref();

    // Calculate the normal
    ofVec3f normal = (anchor - a->position).normalized();
    contact->contactNormal = -normal;
    contact->penetration =  targetLength - currentLen;

	contactRegstry->append(contact);
}


const String MinAnchoredConstraint::toString() const {
	std::ostringstream outs;
	return outs.str();
}
    
    
} }