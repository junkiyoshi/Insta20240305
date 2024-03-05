#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofNoFill();
	ofSetLineWidth(1.5);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->noise_param = ofRandom(1000);
}
//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 25) {

		this->noise_param += ofMap(ofGetFrameNum() % 50, 0, 25, 0.1, 0.005);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofColor color;
	for (int deg = 0; deg < 360; deg += 6) {

		float  radius = 200;

		auto start = glm::vec2((radius - 60) * cos(deg * DEG_TO_RAD), (radius - 60) * sin(deg * DEG_TO_RAD));
		auto end = glm::vec2((radius + 60) * cos(deg * DEG_TO_RAD), (radius + 60) * sin(deg * DEG_TO_RAD));

		auto target_radius = ofMap(ofNoise(cos(deg * DEG_TO_RAD) * 5, sin(deg * DEG_TO_RAD) * 5, this->noise_param), 0, 1, radius - 120, radius + 120);		auto target_location = glm::vec2(target_radius * cos(deg * DEG_TO_RAD), target_radius * sin(deg * DEG_TO_RAD));

		color.setHsb(ofMap(target_radius, radius - 120, radius + 120, 180, 255), 255, 255);
		ofSetColor(color);

		ofDrawLine(start, end);

		ofPushMatrix();
		ofTranslate(target_location);
		ofRotate(deg);

		ofDrawRectangle(glm::vec2(), 100, 8);

		ofPopMatrix();
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}