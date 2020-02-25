#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);
	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto radius = 150;
	for (int x = -250; x <= 250; x += 20) {

		int deg_start = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, 360);
		int start_index = this->face.getNumVertices();
		for (int deg = deg_start; deg < deg_start + 120; deg += 3) {

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(x + 9.9, radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(x + 9.9, radius * cos((deg + 3) * DEG_TO_RAD), radius * sin((deg + 3) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(x - 9.9, radius * cos((deg + 3) * DEG_TO_RAD), radius * sin((deg + 3) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(x - 9.9, radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
		}

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 3);
		this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateX(180);

	auto word = "Hidden";
	auto base_location = glm::vec2(this->font.stringWidth(word) * -0.5, this->font.stringHeight(word) * 0.5);
	auto param = ofGetFrameNum();

	vector<ofPath> word_path = this->font.getStringAsPoints(word, true, false);
	for (int word_index = 0; word_index < word_path.size(); word_index++) {

		vector<ofPolyline> outline = word_path[word_index].getOutline();

		ofFill();
		ofSetColor(39);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			vector<glm::vec3> vertices = outline[outline_index].getVertices();
			for (auto& vertex : vertices) { vertex += glm::vec3(base_location, 0); }

			ofVertices(vertices);
		}
		ofEndShape();
	}

	ofSetColor(239);
	this->face.drawFaces();

	ofSetColor(39);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}