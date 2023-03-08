#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


private:
	ofMesh terrainMesh {};
	ofVbo terrainVbo {};
	ofShader terrainShader {};

	int prevX { 0 };
	int prevY { 0 };
	const float mouseSensitivity { 0.02f };

	const glm::vec3 vX { 1, 0, 0 };
	const glm::vec3 vY { 0, 1, 0 };
	glm::vec3 velocity { 0, 0, 0 };
	glm::vec3 position { 50, 50, 200 };

	float cameraHead { 0 };
	float cameraPitch { 0 };
	void updateCameraRotation(float dx, float dy);

	bool shadersNeedReload { true };
	void reloadShaders();
};
