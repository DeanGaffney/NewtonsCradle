/**
	@file 		ForceGenerators.h
	@author		kmurphy
	@practical 	
	@brief		
	*/

#ifndef PARTICLE_FORCE_GENERATORS_H
#define PARTICLE_FORCE_GENERATORS_H

#include "../Particle.h"

namespace YAMPE { 
	
class Particle;

namespace P {

class ForceGenerator: public Printable {
	
public:
	ForceGenerator(const String label="ForceGenerator") : Printable(label) {};
	
	virtual void applyForce(Particle::Ref particle, float dt) = 0;
	
	typedef ofPtr<ForceGenerator> Ref;
};

// --------------------------------------------------------

/**
	\class GravityForceGenerator ParticleForceGenerators.h
	
	A force generator that applies a gravitational force. 

	One instance can be used for multiple particles. However it is more efficient to
	simply set the acceleration property of each particle. And that approach also 
	allows for different values of g for different objects in the simulation.
	*/
class GravityForceGenerator : public ForceGenerator {

private:

	ofVec3f m_gravity;		///< Holds the acceleration due to gravity

public:
		
	GravityForceGenerator(const ofVec3f &gravity, const String label="GravityForceGenerator");
	virtual void applyForce(Particle::Ref particle, float dt);

	const String toString() const;
};

// --------------------------------------------------------

/**
	\class DragForceGenerator ParticleForceGenerators.h
	
	A force generator that applies a drag force. 
	One instance can be used for multiple particles.
	*/
class DragForceGenerator : public ForceGenerator {

private:	

	float m_k1;			///< velocity drag coeffificent
	float m_k2;			///< velocity squared drag coeffificent
	
public:
	
	DragForceGenerator(float k1, float k2, const String label="DragForceGenerator");	
	virtual void applyForce(Particle::Ref particle, float dt);

	const String toString() const;
};


// --------------------------------------------------------

/*
 	\class SpringForceGenerator ParticleForceGenerators.h

	Force generator for a spring force.

	*/
class SpringForceGenerator : public ForceGenerator {
	
private:
	
	Particle::Ref m_other;		///< Particle at other end of spring.
	float m_springConstant;		///< The sprint constant.
	float m_restLength;			///< The rest length of the spring.
		
public:
		
	SpringForceGenerator(Particle::Ref other, float springConstant, float restLength, const String label="SpringForceGenerator");
	virtual void applyForce(Particle::Ref particle, float dt);

	const String toString() const;
};


// --------------------------------------------------------

/*
	\class AnchoredSpringForceGenerator ParticleForceGenerators.h
 	
	Force generator for a anchored spring force.

	*/
class AnchoredSpringForceGenerator : public ForceGenerator {

private:	
	
	const ofVec3f m_anchor;		///< Position of fixed end of spring.
	float m_springConstant;		///< The sprint constant.
	float m_restLength;			///< The rest length of the spring.
	
public:
	
	AnchoredSpringForceGenerator(const ofVec3f& anchor, float springConstant, float restLength, const String label="AnchoredSpringForceGenerator");
	virtual void applyForce(Particle::Ref particle, float dt);

	const String toString() const;
};


// --------------------------------------------------------

/*
	\class BungeeForceGenerator ParticleForceGenerators.h
 	
	Force generator for a bungee force.

	*/
class BungeeForceGenerator : public ForceGenerator {

private:	
	
	Particle::Ref m_other;		///< The particle at the other end of the spring.
	float m_springConstant;		///< Holds the sprint constant.
	float m_restLength;			///< Holds the rest length of the spring.
	
public:

	BungeeForceGenerator(Particle::Ref other, float springConstant, float restLength, const String label="BungeeForceGenerator");
	virtual void applyForce(Particle::Ref particle, float dt);

	const String toString() const;
};


// --------------------------------------------------------

/*
	\class AnchoredBungeeForceGenerator ParticleForceGenerators.h
 	
	Force generator for a bungee force.

	*/
class AnchoredBungeeForceGenerator : public ForceGenerator {

private:	
	
	const ofVec3f m_anchor;		///< Position of fixed end of spring.
	float m_springConstant;		///< The sprint constant.
	float m_restLength;			///< The rest length of the spring.
	
public:

	AnchoredBungeeForceGenerator(const ofVec3f& anchor, float springConstant, float restLength, const String label="AnchoredBungeeForceGenerator");
	virtual void applyForce(Particle::Ref particle, float dt);

	const String toString() const;
};

} }	

#endif