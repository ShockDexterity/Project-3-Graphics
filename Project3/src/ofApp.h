#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "CellManager.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void exit();

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

	ofMesh waterMesh {};
	ofShader waterShader {};


	ofShortImage heightmapLowRes {};
	ofShortImage heightmapHiRes {};
	CellManager<5> cm { heightmapHiRes, 1600, 256 };

	int prevX { 0 };
	int prevY { 0 };
	const float mouseSensitivity { 0.02f };

	const glm::vec3 vX { 1, 0, 0 };
	const glm::vec3 vY { 0, 1, 0 };
	glm::vec3 velocity { 0, 0, 0 };

	Camera camera { glm::vec3(50, 50, 200) };

	float cameraHead { 0 };
	float cameraPitch { 0 };
	void updateCameraRotation(float dx, float dy);

	bool shadersNeedReload { true };
	void reloadShaders();
};
