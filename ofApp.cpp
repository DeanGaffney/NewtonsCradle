#include "ofApp.h"

using namespace YAMPE;
using namespace P;
//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // repatable randomness
    ofSeedRandom(10);
    
    // simulation specific stuff goes here

    gui.setup();
    ImGui::GetIO().MouseDrawCursor = false;

    // load parameters from file
    // loadFromFile("settings.xml");
    
    // instantiate the ground
    ground.set(RANGE, RANGE);
    ground.rotate(90, 1,0,0);
    
    // lift camera to 'eye' level
    easyCam.setDistance(RANGE);
    float d = easyCam.getDistance();
    easyCam.setPosition(ofVec3f(0, cameraHeightRatio*d, d*sqrt(1.0f-cameraHeightRatio*cameraHeightRatio))+easyCamTarget);
    easyCam.setTarget(easyCamTarget);

    // TODO - simulation specific stuff goes here
	gravity = GravityForceGenerator::Ref(new GravityForceGenerator(ofVec3f(0.0f, -9.81f, 0.0f), "Gravity Generator"));

	contacts = ContactRegistry::Ref(new ContactRegistry());
    
    // finally start everything off by resetting the simulation
    reset();
    
}

void ofApp::reset() {
    t = 0.0f;
    
	particles.clear();
	forceGenerators.clear();
	ppContactGenerator.particles.clear();
	anchorConstraints.clear();

	startPosX = -(numOfBalls * (BALL_RADIUS * 2 + eps)) / 2;
	float xPos = startPosX;

	for (int k = 0; k < numOfBalls; ++k) {
		//generate particles with rand position, and add to particles
		Particle::Ref ball = Particle::Ref(new Particle());
		ofVec3f anchorPos = ofVec3f(xPos, ANCHOR_HEIGHT, 0.0f);
		ofVec3f ballPos;
		if (k < ballsAtAngle) {
			float angle = 90.0f - ballAngle;
			ballPos.x -= (ANCHOR_LENGTH * ofRadToDeg(cosf(ofDegToRad(angle))));
			ballPos.y -= (ANCHOR_LENGTH * ofRadToDeg(sinf(ofDegToRad(angle))));
			ballPos.z = 0.0f;
		}
		else {
			ballPos.x = xPos;
			ballPos.y -= ANCHOR_LENGTH;
		}

		ball->setPosition(ballPos).setRadius(BALL_RADIUS)
			.setBodyColor({ 255 , 0, 0 })
			.setVelocity(ofVec3f::zero())
			.acceleration = ofVec3f::zero();

		//set up anchors first
		EqualityAnchoredConstraint::Ref constraint = EqualityAnchoredConstraint::Ref(new EqualityAnchoredConstraint(ball, anchorPos, ANCHOR_LENGTH));
		
		anchorConstraints.push_back(constraint);
		particles.push_back(ball);
		forceGenerators.add(ball, gravity);
		ppContactGenerator.particles.push_back(ball);

		xPos += BALL_RADIUS * 2.0f + eps;
	}
}

void ofApp::update() {

    float dt = ofClamp(ofGetLastFrameTime(), 0.0, 0.02);
    if (dt <= 0.0f || !isRunning) return;
    t += dt;

	forceGenerators.applyForce(dt);
	for (auto p : particles) p->integrate(dt);
	
	//loop and update constraints
	for (auto c : anchorConstraints) c->generate(contacts);

	ppContactGenerator.generate(contacts);

	contacts->resolve(dt);
	contacts->clear();
}

void ofApp::draw() {
    
    ofEnableDepthTest();
    ofBackgroundGradient(ofColor(128), ofColor(0), OF_GRADIENT_BAR);
    
    ofPushStyle();
    easyCam.begin();
    
    ofDrawGrid(RANGE/(2*8), 8, false, isXGridVisible, isYGridVisible, isZGridVisible);
    
    if (isAxisVisible) ofDrawAxis(1);
    
    if (isGroundVisible) {
        ofPushStyle();
        ofSetHexColor(0xB87333);
        ground.draw();
        ofPopStyle();
    }


	float xPos = startPosX;
	for (auto p : particles) {
		ofSetColor(255, 255, 255);
		ofDrawLine(xPos, ANCHOR_HEIGHT, p->position.x, p->position.y);
		ofDrawSphere(xPos, ANCHOR_HEIGHT, 0.1f);
		p->draw();
		xPos += BALL_RADIUS * 2.0f + eps;
	}

	ofDrawLine(-(particles.size() * (BALL_RADIUS * 2 + eps)), ANCHOR_HEIGHT, particles.size() * (BALL_RADIUS * 2 + eps), ANCHOR_HEIGHT);

    easyCam.end();
    ofPopStyle();

    // draw gui elements
    gui.begin();
    drawAppMenuBar();
    drawMainWindow();
    drawLoggingWindow();
    gui.end();
    
}


void ofApp::drawAppMenuBar() {
    
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "")) quit();
            ImGui::EndMenu();
        }
        
        float d = easyCam.getDistance();
        
        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem(isAxisVisible?"Hide Unit Axis":"Show Unit Axis", "")) isAxisVisible = !isAxisVisible;
            if (ImGui::MenuItem(isGroundVisible?"Hide Ground":"Show Ground", "")) isGroundVisible = !isGroundVisible;
            if (ImGui::MenuItem(isXGridVisible?"Hide Grid (X)":"Show Grid (X)", "")) isXGridVisible = !isXGridVisible;
            if (ImGui::MenuItem(isYGridVisible?"Hide Grid (Y)":"Show Grid (Y)", "")) isYGridVisible = !isYGridVisible;
            if (ImGui::MenuItem(isZGridVisible?"Hide Grid (Z)":"Show Grid (Z)", "")) isZGridVisible = !isZGridVisible;
            ImGui::Separator();
            if (ImGui::MenuItem("Align camera above X axis ", "")) {
                easyCam.setPosition(ofVec3f(d*sqrt(1.0f-cameraHeightRatio*cameraHeightRatio), cameraHeightRatio*d, 0)+easyCamTarget);
                easyCam.setTarget(easyCamTarget);
            }
            if (ImGui::MenuItem("Align camera above Z axis ", "")) {
                easyCam.setPosition(ofVec3f(0, cameraHeightRatio*d, d*sqrt(1.0f-cameraHeightRatio*cameraHeightRatio))+easyCamTarget);
                easyCam.setTarget(easyCamTarget);
                cout <<"here";
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Align camera along X axis ", "")) {
                easyCam.setPosition(ofVec3f(d, 0, 0)+easyCamTarget);
                easyCam.setTarget(easyCamTarget);
            }
            if (ImGui::MenuItem("Align camera along Y axis ", "")) {
                easyCam.setPosition(ofVec3f(0.001, d, 0)+easyCamTarget);
                easyCam.setTarget(easyCamTarget);
            }
            if (ImGui::MenuItem("Align camera along Z axis ", "")) {
                easyCam.setPosition(ofVec3f(0, 0, d)+easyCamTarget);
                easyCam.setTarget(easyCamTarget);
            }
            
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Application")) {
            if (ImGui::MenuItem("Add application specific menu items here", "")) {
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}


void ofApp::drawMainWindow() {
    

    ImGui::SetNextWindowPos(ImVec2(0,20), ImGuiSetCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300,300), ImGuiSetCond_FirstUseEver);
    if (ImGui::Begin("Main")) {

        if (ImGui::CollapsingHeader("3D")) {
            if(ImGui::Button("Reset##CameraTarget")) {
                easyCamTarget = ofVec3f(0,5,0);
                easyCam.setTarget(easyCamTarget);
            }

            ImGui::SameLine();
            if (ImGui::InputFloat3("Camera Target", &easyCamTarget.x)) {
                easyCam.setTarget(easyCamTarget);
            }
            if (ImGui::SliderFloat("Camera Height Ratio", &cameraHeightRatio, 0.0f, 1.0f))
                cameraHeightRatioChanged(cameraHeightRatio);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        if(ImGui::Button("Reset")) reset();
        ImGui::SameLine();
        if(ImGui::Button(isRunning?"Stop":" Go ")) isRunning = !isRunning;
        ImGui::SameLine();
        ImGui::Text("   Time = %8.1f", t);
        if(ImGui::Button("Quit")) quit();
        
		// TODO - numeric output goes here
		if (ImGui::SliderInt("Number of Balls", &numOfBalls, MIN_BALLS, MAX_BALLS)) reset();
		if (ImGui::SliderInt("Balls at an angle", &ballsAtAngle, MIN_BALLS, MAX_BALLS))reset();
		if (ImGui::SliderFloat("Ball angle", &ballAngle, MIN_BALL_ANGLE, MAX_BALL_ANGLE)) reset();
		if (ImGui::SliderFloat("Epsilon (spacing)", &eps, 0.0f, 1.0f)) reset();

        
        if (ImGui::CollapsingHeader("Numerical Output")) {
            
        }
        
        if (ImGui::CollapsingHeader("Graphical Output")) {
            // TODO - graphical output goes here
        }
    }
    
    // store window size so that camera can ignore mouse clicks
    mainWindowRectangle.setPosition(ImGui::GetWindowPos().x,ImGui::GetWindowPos().y);
    mainWindowRectangle.setSize(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
    ImGui::End();

}


void ofApp::drawLoggingWindow() {
    ImGui::SetNextWindowSize(ImVec2(290,300), ImGuiSetCond_Always);
    ImGui::SetNextWindowPos(ImVec2(ofGetWindowWidth()-300,20), ImGuiSetCond_Always);
    
    if (ImGui::Begin("Logging")) {
    }
    // store window size so that camera can ignore mouse clicks
    loggingWindowRectangle.setPosition(ImGui::GetWindowPos().x,ImGui::GetWindowPos().y);
    loggingWindowRectangle.setSize(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
    ImGui::End();
}

//--------------------------------------------------------------
// GUI events and listeners
//--------------------------------------------------------------

void ofApp::keyPressed(int key) {
    
    float d = easyCam.getDistance();
    
    switch (key) {
        
//        case 'h':                               // toggle GUI/HUD
//           isGuiVisible = !isGuiVisible;
//            break;
//        case 'b':                               // toggle debug
//            isDebugVisible = !isDebugVisible;
//            break;
//        case 'a':                               // toggle axis unit vectors
//            isAxisVisible = !isAxisVisible;
//            break;
//        case 'g':                               // toggle ground
//            isGroundVisible = !isGroundVisible;
//            break;
//        case 'u':                               // set the up vecetor to be up (ground to be level)
//            easyCam.setTarget(ofVec3f::zero());
//            break;
//
//        case 'S' :                              // save gui parameters to file
//            gui.saveToFile("settings.xml");
//
//            break;
//        case 'L' :                              // load gui parameters
//            gui.loadFromFile("settings.xml");
//            break;
//
        case 'z':
            easyCam.setPosition(ofVec3f(0, cameraHeightRatio*d, d*sqrt(1.0f-cameraHeightRatio*cameraHeightRatio))+easyCamTarget);
            easyCam.setTarget(easyCamTarget);
            break;
        case 'Z':
            easyCam.setPosition(0, 0, d);
            easyCam.setTarget(ofVec3f::zero());
            break;
        case 'x':
            easyCam.setPosition(ofVec3f(d*sqrt(1.0f-cameraHeightRatio*cameraHeightRatio), cameraHeightRatio*d, 0)+easyCamTarget);
            easyCam.setTarget(easyCamTarget);
            break;
        case 'X':
            easyCam.setPosition(ofVec3f(d, 0, 0)+easyCamTarget);
            easyCam.setTarget(easyCamTarget);
            break;
        case 'Y':
            easyCam.setPosition(ofVec3f(0.001, d, 0)+easyCamTarget);
            easyCam.setTarget(easyCamTarget);
            break;
            
        case 'f':                               // toggle fullscreen
            // BUG: window size is not preserved
            isFullScreen = !isFullScreen;
            if (isFullScreen) {
                ofSetFullscreen(false);
            } else {
                ofSetFullscreen(true);
            }
            break;

        // simulation specific stuff goes here

    }
}


void ofApp::cameraHeightRatioChanged(float & cameraHeightRatio) {
    
    float d = easyCam.getDistance();
    easyCam.setPosition(ofVec3f(0, cameraHeightRatio*d, d*sqrt(1.0f-cameraHeightRatio*cameraHeightRatio))+easyCamTarget);
    easyCam.setTarget(easyCamTarget);
}


void ofApp::quit() {
    ofExit();
}

//--------------------------------------------------------------
// Unused
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y ) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {
    // easy camera should ignore GUI mouse clicks
    if (mainWindowRectangle.inside(x,y)||loggingWindowRectangle.inside(x,y))
        easyCam.disableMouseInput();
    else
        easyCam.enableMouseInput();
}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
