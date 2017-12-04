/**
	@file 		Particle.cpp 
	@author		kmurphy
	@practical 	
	@brief		Implemention of a particle (point mass) class.
	*/

#include "Particle.h"

namespace YAMPE {

Particle& Particle::setMass(float mass) {
	ASSERT (mass != 0.0f, "Expected positive mass for particle.");
	m_inverseMass = 1.0f/mass;
	return *this;
}

float Particle::mass() const {
    return 1.0f/m_inverseMass;
}

Particle& Particle::setInverseMass(float inverseMass) {
	m_inverseMass = inverseMass;
	return *this;
}

float Particle::inverseMass() const {
	return m_inverseMass;
}

bool Particle::hasFiniteMass() const {
    return m_inverseMass > 0.0f;
}


void Particle::integrate(float dt) {
	
	// An unmovable particle has zero inverseMass. 
	if (m_inverseMass <= 0.0f) return;
	
	// Verify a non-zero time step.
	ASSERT(dt > 0.0f, "Expected a non-zero time step in Particle::Integrate");
		
	// Work out the acceleration from the force.
	ofVec3f resultingAcceleration(acceleration + m_inverseMass*m_force);
	
	// Update linear velocity from the acceleration.
	velocity +=  dt*resultingAcceleration;
	
	// Impose artificial drag.
	velocity *= pow(m_damping, dt);

	// Update linear position.
	position += dt*velocity;
	
	force = m_force;
	
	// Clear the forces.
	clearForce();
	
}

Particle& Particle::setDamping(float damping) {
	m_damping = damping;
	return *this;
}

float Particle::damping() const {
	return m_damping;
}

void Particle::clearForce() {
	m_force.x = m_force.y = m_force.z = 0.0f;
}

Particle& Particle::applyForce(const ofVec3f& force) {
	m_force += force;
	return *this;
}

Particle& Particle::setLabel(String label) {
	Printable::setLabel(label);
	return *this;
}

Particle& Particle::setPosition(const ofVec3f& position) {
	this->position = position;
	return *this;
}

Particle& Particle::setVelocity(const ofVec3f& velocity) {
	this->velocity = velocity;
	return *this;
}
	
Particle& Particle::setRadius(float radius){
	this->radius = radius;
	return *this;
}

Particle& Particle::setBodyColor(const ofColor bodyColor) {
	this->bodyColor = bodyColor;
	return *this;
}

Particle& Particle::setWireColor(const ofColor wireColor) {
	this->wireColor = wireColor;
	return *this;
}

const String Particle::toString() const {
	std::ostringstream outs;
	outs<<"Position = " <<position <<"    "
		<<"Velocity = " <<velocity <<"    "
		<<"Acceleration = " <<acceleration;
	return outs.str();
}

void Particle::draw() {
        
    ofPushStyle();
    ofFill();
    ofSetColor(bodyColor);
    ofDrawSphere(position, radius);
    ofNoFill();
    ofSetColor(wireColor);
    ofDrawSphere(position, radius);
    if (isForceVisible) {
        ofFill();
        ofSetColor(ofColor::blue);
        ofDrawArrow(position, position+force);
    }
    ofPopStyle();
}

}	// namespace YAMPE

