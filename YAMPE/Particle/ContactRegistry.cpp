/**
	@file 		P_ContactRegistry.cpp
	@author		kmurphy
	@practical 	
	@brief	
	*/

#include <cfloat>
#include "Contact.h"
#include "ContactRegistry.h"

namespace YAMPE { namespace P {


ContactRegistry::ContactRegistry (unsigned iterationLimit, String label) :
	Printable(label), m_iterationLimit(iterationLimit), registry() { }


void ContactRegistry::resolve(float dt) {

	for (m_iterationUsed=0; m_iterationUsed < m_iterationLimit; ++m_iterationUsed) {

        // Find the contact with the largest closing velocity.
		//
		// This contact is the first to be resolved.
		// We are only interested in contacts where the seperating velocity
		// is negative (ie moving closer) or have (+ive) penetration.
        float max = FLT_MAX;
        Contact::Ref maxContact;
        for (auto && contact: registry) {
            float sepVel = contact->calculateSeparatingVelocity();
            if (sepVel < max && (sepVel < 0 || contact->penetration > 0)) {
                max = sepVel;
				maxContact = contact;
            }
        }
		
		// Exit algorithm if we do not have any contacts worth resolving.
		if (maxContact==NULL || (max>-EPS && maxContact->penetration<EPS)) return;
		
        // Resolve this contact.
        maxContact->resolve(dt);
		
		// Update the interpenetrations for all particles.
		//
		// As a result of resolving contact maxContact the involved
		// particle(s) may have to be moved. We therefore check all other 
		// contacts for these particles and update their position and 
		// hence the contact penetration accordinaly.
		ofVec3f aMovement = maxContact->aMovement;
		ofVec3f bMovement = maxContact->bMovement;
        for (auto && contact: registry) {
			if (contact->a == maxContact->a) {
				contact->penetration -= aMovement.dot(contact->contactNormal);
			} else if (contact->a == maxContact->b) {
                contact->penetration -= bMovement.dot(contact->contactNormal);
			}		
			if (contact->b!=NULL) {
				if (contact->b == maxContact->a) {
					contact->penetration += aMovement.dot(contact->contactNormal);
				} else if (contact->b == maxContact->b) {
                    contact->penetration += bMovement.dot(contact->contactNormal);
				}		
			}
		}
		// debugPrintf ("DEBUG iter=%d contact %s aMovememt=(%f,%f,%f), bMovement=(%f,%f,%f) max=%f, pen=%f\n",
		// 	m_iterationUsed, maxContact->label().c_str(),
		// 	aMovement.x, aMovement.y, aMovement.z,
		// 	bMovement.x, bMovement.y, bMovement.z,
		// 	max,
		// 	maxContact->penetration
		// 	); 
    }

	// Reached iteration limit => may still have unresolved contacts.
	ofLog(OF_LOG_WARNING, "[ContactRegistry::resolve] Reached iteration limit (%d).\n",
		m_iterationLimit);
}


void ContactRegistry::append(Contact::Ref contact) {
	registry.push_back(contact);
}


void ContactRegistry::clear() {
	registry.clear();
}


const String ContactRegistry::toString() const {
	std::ostringstream outs;
	for (Registry::const_iterator it = registry.begin(); it!=registry.end(); ++it) {
		outs <<"\nContact\n" <<"\t " <<*(it) <<"\n""\n";
    }
	outs <<"\n";
	return outs.str();
}
} }

