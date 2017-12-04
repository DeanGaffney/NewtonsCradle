/**
	@file 		ForceGeneratorRegistry.cpp
	@author		kmurphy
	@practical 	
	@brief		Implementation of registry class to store current force generators between particles.
	*/

#include "ForceGeneratorRegistry.h"

namespace YAMPE { namespace P {
		
void ForceGeneratorRegistry::applyForce(float dt) {
    for (auto && it: registry) {
		it.forceGenerator->applyForce(it.particle, dt);
    }
}

void ForceGeneratorRegistry::add(Particle::Ref particle, ForceGenerator::Ref  forceGenerator) {
	ForceGeneratorRegistry::Entry entry(particle, forceGenerator);
	registry.push_back(entry);
}

const String ForceGeneratorRegistry::toString() const {
	std::ostringstream outs;
	for (Registry::const_iterator it = registry.begin(); it!=registry.end(); ++it) {
		outs <<"\nEntry\n" 
			<<"\t " <<*(it->forceGenerator) <<"\n"
			<<"\t " <<*(it->particle) <<"\n";
    }
	outs <<"\n";
	return outs.str();
}

void ForceGeneratorRegistry::clear() {
    registry.clear();
}

} }	// namespace YAMPE::P
