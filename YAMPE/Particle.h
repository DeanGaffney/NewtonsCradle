/**
	@file 		Particle.h
	@author		kmurphy
	@practical 	
	@brief		Specification of a particle (point mass) class.
	*/

#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
#include "Printable.h"

namespace YAMPE {

/** 
	A particle is the simplest object that can be simulated in the physics system.

	A particle is a point-mass with velocity and acceleration.
	
 */
class Particle : public Printable {
	
private:
	float m_inverseMass;		///< 1/mass of object (see notes).
	float m_damping;			///< Artifical damping (see notes).
	ofVec3f m_force;			///< (Sum of) forces applied to particle.
	
public:	
    typedef ofPtr<Particle> Ref;

	float radius;
	ofColor bodyColor;
	ofColor wireColor;
	bool visible;
	bool isForceVisible;		///< flag - display force on particle
	ofVec3f force;				///< force at last call to integrate (for display only)

	ofVec3f position;			///< Particle position.
	ofVec3f velocity;			///< Particle velocity (rate of change of position).
	ofVec3f acceleration;		///< Particle acceleration (rate of change of velocity).

	/** 
		Default particle has an inverse mass and damping of values of one and
		is fixed at the origin.
	*/
	Particle() : 
		Printable("Particle"),
		m_inverseMass(1.0f), 
		m_damping(1.0f), 
		m_force(ofVec3f::zero()),
		
		radius(0.1f),
		bodyColor(ofColor::black),
		wireColor(ofColor::black),
		visible(true),
		isForceVisible(false),
		
		force(ofVec3f::zero()),
		position(ofVec3f::zero()), 
		velocity(ofVec3f::zero()), 
		acceleration(ofVec3f::zero())
	{ }

	Particle& setLabel(String label);
	Particle& setPosition(const ofVec3f& position);
	Particle& setVelocity(const ofVec3f& velocity);
	Particle& setRadius(float radius);
	Particle& setBodyColor(const ofColor bodyColor);
	Particle& setWireColor(const ofColor wireColor);
	
	virtual const String toString() const;

	Particle& setMass(float mass);
	float mass() const;

	Particle& setInverseMass(float inverseMass);
	float inverseMass() const;

	bool hasFiniteMass() const;
	
	void integrate(float dt);

	Particle& setDamping(float damping);
	float damping() const;
        	
	void clearForce();
	Particle& applyForce(const ofVec3f& force);
	
	virtual void draw();
};

typedef vector<Particle::Ref> ParticleRegistry;
    
}	// namespace YAMPE

#endif