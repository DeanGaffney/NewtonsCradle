/**
	@file 		ForceGenerators.cpp
	@author		kmurphy
	@practical 	
	@brief		Implementation of various simple force generators.
	*/

#include "ForceGenerators.h"

namespace YAMPE { namespace P {

// --------------------------------------------------------

GravityForceGenerator::GravityForceGenerator(const ofVec3f& gravity,
	const String label) : ForceGenerator(label), m_gravity(gravity) { }
	

void GravityForceGenerator::applyForce(Particle::Ref particle, float dt) {
	(void) dt;
	
	// Do nothing if particle has infinite mass
    if (!particle->hasFiniteMass()) return;
	
    // Apply the mass-scaled force to the particle
    particle->applyForce(m_gravity * particle->mass());
}


const String GravityForceGenerator::toString() const {
	std::ostringstream outs;
	outs <<"\t gravity = " <<m_gravity;
	return outs.str();
}

// --------------------------------------------------------

DragForceGenerator::DragForceGenerator(float k1, float k2, const String label) 
	: ForceGenerator(label), m_k1(k1), m_k2(k2) { }


void DragForceGenerator::applyForce(Particle::Ref particle, float dt) {
	(void) dt;
	
    float dragCoeff = -(m_k1 + m_k2*particle->velocity.length());
	
    particle->applyForce(particle->velocity*dragCoeff);
}


const String DragForceGenerator::toString() const {
	std::ostringstream outs;
	outs <<"\t k1 = " <<m_k1 <<"\t k2 = " <<m_k2;
	return outs.str();
}

// --------------------------------------------------------

SpringForceGenerator::SpringForceGenerator(Particle::Ref other, 
	float springConstant, float restLength, const String label) 
	: ForceGenerator(label), m_other(other), m_springConstant(springConstant), m_restLength(restLength) { }


void SpringForceGenerator::applyForce(Particle::Ref particle, float dt) {
	(void) dt;

    // Calculate the vector of the spring
    ofVec3f force(particle->position - m_other->position);
	
    // Calculate the magnitude of the force
	float currentLength = force.length();
    float length = m_springConstant * abs(currentLength - m_restLength);
    force *= (-length/currentLength);
	
    particle->applyForce(force);
}


const String SpringForceGenerator::toString() const {
	std::ostringstream outs;
	outs <<"Other point = " <<*m_other <<"    "
		<<"springConstant = " <<m_springConstant <<"    "
		<<"restLength = " <<m_restLength <<"    ";
	return outs.str();
}

// --------------------------------------------------------

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(const ofVec3f& anchor,
		float springConstant, float restLength, const String label) 
	: ForceGenerator(label), m_anchor(anchor), m_springConstant(springConstant), m_restLength(restLength) { }


void AnchoredSpringForceGenerator::applyForce(Particle::Ref particle, float dt) {
	(void) dt;
	
    // Calculate the vector of the spring
    ofVec3f force = particle->position - m_anchor;

    // Calculate the magnitude of the force
	float currentLength = force.length();
    float length = (currentLength - m_restLength)*m_springConstant;
    force *= (-length/currentLength) ;
		
    particle->applyForce(force);	
}


const String AnchoredSpringForceGenerator::toString() const {
	std::ostringstream outs;
	outs <<"Anchor =  " <<m_anchor <<"    "
		<<"springConstant = " <<m_springConstant
		<<"restLength = " <<m_restLength <<"    ";
	return outs.str();
}

// --------------------------------------------------------

BungeeForceGenerator::BungeeForceGenerator(Particle::Ref other, 
	float springConstant, float restLength, const String label) 
	: ForceGenerator(label), m_other(other), m_springConstant(springConstant), m_restLength(restLength) { }


void BungeeForceGenerator::applyForce(Particle::Ref particle, float dt) {
	(void) dt;

    // Calculate the vector of the spring
    ofVec3f force = particle->position - m_other->position;
	
    // Calculate the magnitude of the force
	float currentLength = force.length();
	
	if (currentLength <= m_restLength) return; 	// A compressed bungee raises no force
    float length = m_springConstant * (currentLength - m_restLength);
    force *= (-length/currentLength) ;
	
    particle->applyForce(force);
}


const String BungeeForceGenerator::toString() const {
	std::ostringstream outs;
	outs <<"Other point = " <<*m_other <<"    "
		<<"springConstant = " <<m_springConstant <<"    "
		<<"restLength = " <<m_restLength <<"    ";
	return outs.str();
}

// --------------------------------------------------------

AnchoredBungeeForceGenerator::AnchoredBungeeForceGenerator(const ofVec3f& anchor,
	float springConstant, float restLength, const String label) 
	: ForceGenerator(label), 
	m_anchor(anchor), m_springConstant(springConstant), m_restLength(restLength) { }


void AnchoredBungeeForceGenerator::applyForce(Particle::Ref particle, float dt) {
	(void) dt;

    // Calculate the vector of the spring
    ofVec3f force = particle->position - m_anchor;
	
    // Calculate the magnitude of the force
	float currentLength = force.length();
	
	if (currentLength <= m_restLength) return; 	// A compressed bungee raises no force
    float length = m_springConstant * (currentLength - m_restLength);
    force *= (-length/currentLength) ;
	
    particle->applyForce(force);
}

const String AnchoredBungeeForceGenerator::toString() const {
	std::ostringstream outs;
	outs <<"Anchor = " <<m_anchor <<"    "
		<<"springConstant = " <<m_springConstant <<"    "
		<<"restLength = " <<m_restLength <<"    ";
	return outs.str();
}

} }
