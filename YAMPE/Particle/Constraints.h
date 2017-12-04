/**
	@file 		Constraints.h
	@author		kmurphy
	@practical 	
	@brief		Classes supporting various constraints between Particles.
	*/
	
// TODO
// change constructors to allow for setting of parameters

#ifndef PARTICLE_CONSTRAINTS_H
#define PARTICLE_CONSTRAINTS_H

#include "ContactGenerators.h"

namespace YAMPE { namespace P {
	
class Constraint: public ContactGenerator {
public:
	Particle::Ref a;
	Particle::Ref b;

	float targetLength;
	float restitution;	
	
public:
	Constraint(Particle::Ref a=Particle::Ref(), Particle::Ref b=Particle::Ref(),
		float targetLength=1.0f, float restitution=1.0f, 
		const String label="Constraint") 
		: ContactGenerator(label), a(a), b(b), targetLength(targetLength), restitution(restitution) { };

	float currentLength() const;
	
};


// --------------------------------------------------------


class EqualityConstraint: public Constraint {
public:
	EqualityConstraint(Particle::Ref a=Particle::Ref(), Particle::Ref b=Particle::Ref(),
		float targetLength=1.0f, float restitution=0.0f, 
		const String label="EqualityConstraint") 
		: Constraint(a,b,targetLength,restitution,label) { };
		
	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


// --------------------------------------------------------


class MaxConstraint: public Constraint {
public:
	MaxConstraint(Particle::Ref a=Particle::Ref(), Particle::Ref b=Particle::Ref(),
		float targetLength=1.0f, float restitution=1.0f, 
		const String label="MaxConstraint") 
		: Constraint(a,b,targetLength,restitution,label) { };
		
	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


// --------------------------------------------------------


class MinConstraint: public Constraint {
public:
	MinConstraint(Particle::Ref a=Particle::Ref(), Particle::Ref b=Particle::Ref(),
		float targetLength=1.0f, float restitution=1.0f, 
		const String label="MinConstraint") 
		: Constraint(a,b,targetLength,restitution,label) { };
		
	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


// --------------------------------------------------------


class AnchoredConstraint: public ContactGenerator {
public:
	Particle::Ref a;
	ofVec3f anchor;
	float targetLength;
	float restitution;	
	
public:
	AnchoredConstraint(Particle::Ref a=Particle::Ref(), ofVec3f anchor=ofVec3f::zero(),
		float targetLength=1.0f, float restitution=1.0f, 
		const String label="AnchoredConstraint") 
		: ContactGenerator(label), a(a), anchor(anchor), targetLength(targetLength), restitution(restitution) { };

	float currentLength() const;	
};


// --------------------------------------------------------


class EqualityAnchoredConstraint: public AnchoredConstraint {
public:
	EqualityAnchoredConstraint(Particle::Ref a=Particle::Ref(), ofVec3f anchor=ofVec3f::zero(),
		float targetLength=1.0f, float restitution=0.0f, 
		const String label="EqualityAnchoredConstraint") 
		: AnchoredConstraint(a,anchor,targetLength,restitution,label) { };
		
	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


// --------------------------------------------------------


class MaxAnchoredConstraint: public AnchoredConstraint {
public:
	MaxAnchoredConstraint(Particle::Ref a=Particle::Ref(), ofVec3f anchor=ofVec3f::zero(),
		float targetLength=1.0f, float restitution=1.0f, 
		const String label="MaxAnchoredConstraint") 
		: AnchoredConstraint(a,anchor,targetLength,restitution,label) { };
		
	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


// --------------------------------------------------------


class MinAnchoredConstraint: public AnchoredConstraint {
public:
	MinAnchoredConstraint(Particle::Ref a=Particle::Ref(), ofVec3f anchor=ofVec3f::zero(),
		float targetLength=1.0f, float restitution=1.0f, 
		const String label="MinAnchoredConstraint") 
		: AnchoredConstraint(a,anchor,targetLength,restitution,label) { };
	
	void generate(ContactRegistry::Ref contactRegstry);
	
	const String toString() const;
};


}}
#endif

