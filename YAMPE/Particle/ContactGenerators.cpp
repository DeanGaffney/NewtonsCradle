/**
	@file 		P_ContactGenerators.cpp
	@author		kmurphy
	@practical 	
	@brief	
	*/

#include "ContactGenerators.h"
#include "ContactRegistry.h"
#include "../Particle.h"

namespace YAMPE { namespace P {

// --------------------------------------------------------
void GroundContactGenerator::generate(ContactRegistry::Ref contactRegistry) {

    for (auto && p: particles) {
		float y = p->position.y - p->radius;
		if (y<0.0f) {
            Contact::Ref contact(new Contact("GroundContactGenerator"));
			contact->contactNormal = ofVec3f(0,1,0);
            contact->a = p;
            contact->b = Particle::Ref();
            contact->penetration = -y;
            contact->restitution = 1.0f;
			contactRegistry->append(contact);
		}
	}
}



const String GroundContactGenerator::toString() const {
	std::ostringstream outs;
	return outs.str();
}


// --------------------------------------------------------

void ParticleParticleContactGenerator::generate(ContactRegistry::Ref contactRegistry) {

	for(ParticleRegistry::iterator a=particles.begin(); a!=particles.end(); ++a) {
		for(ParticleRegistry::iterator b=particles.begin(); b!=a; ++b) {

			// get approach normal
			ofVec3f normal = (*a)->position - (*b)->position;
			float distance = normal.length();
			
			// if particles are closer than their radi then generate contact
			if (distance<(*a)->radius+(*b)->radius) {
                Contact::Ref contact(new Contact("ParticleParticleContactGenerator"));
				contact->contactNormal = normal.normalize();
				contact->a = *a;
				contact->b = *b;
				contact->penetration = -distance + (*a)->radius + (*b)->radius;
	            contact->restitution = 1.0f;
				contactRegistry->append(contact);
			}
		}
	}
}



const String ParticleParticleContactGenerator::toString() const {
	std::ostringstream outs;
	return outs.str();
}

} }