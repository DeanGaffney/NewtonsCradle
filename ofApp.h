#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

#include "ofxXmlSettings.h"
#include "YAMPE/Particle.h"
#include "YAMPE/Particle/ForceGeneratorRegistry.h"
#include "YAMPE/Particle/ContactRegistry.h"
#include "YAMPE/Particle/ContactGenerators.h"
#include "YAMPE\Particle\Constraints.h"


class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
    // simple 3D world with ground and axes
    const float RANGE = 16;
    ofEasyCam easyCam;
    float cameraHeightRatio = 0.02f;
    ofPoint easyCamTarget = ofPoint(0,5,0);
    void cameraHeightRatioChanged(float & cameraHeightRatio);

    ofPlanePrimitive ground;
    
    ofxImGui::Gui gui;                           // single entry to ImGUI subsystem
    ofRectangle mainWindowRectangle;        // used to ignore mouse drags for camera
    ofRectangle loggingWindowRectangle;     // used to ignore mouse drags for camera
    void drawAppMenuBar();
    void drawMainWindow();
    void drawLoggingWindow();
    
    // simimulation (generic)
    void reset();
    void quit();
    float t = 0.0f;
    bool isRunning = true;
    
    ofParameter<bool> isAxisVisible = true;
    ofParameter<bool> isXGridVisible = false;
    ofParameter<bool> isYGridVisible = true;;
    ofParameter<bool> isZGridVisible = false;;
    ofParameter<bool> isGroundVisible = true;
    ofParameter<bool> isFullScreen;
    ofParameter<std::string> position;

    // TODO - simimulation (specific stuff)
	int numOfBalls{ 1 };
	int ballsAtAngle{ 1 };
	float eps{ 0.0 };
	float ballAngle{ 45 };
	float startPosX{ -RANGE / 2};

	vector<YAMPE::P::EqualityAnchoredConstraint::Ref> anchorConstraints;

	YAMPE::ParticleRegistry particles;
	YAMPE::P::ForceGeneratorRegistry forceGenerators;
	YAMPE::P::GravityForceGenerator::Ref gravity;

	YAMPE::P::ContactRegistry::Ref contacts;
	YAMPE::P::ParticleParticleContactGenerator ppContactGenerator;

	const int MAX_BALLS = 20;
	const int MIN_BALLS = 0;
	const float BALL_RADIUS = 0.5f;
	const float BALL_HEIGHT = 2.0f;
	const float ANCHOR_HEIGHT = 10.0f;
	const float ANCHOR_LENGTH = 5.0f;
	const float MAX_BALL_ANGLE = 90.0f;
	const float MIN_BALL_ANGLE = 0.0f;
private:

    // or here

};
