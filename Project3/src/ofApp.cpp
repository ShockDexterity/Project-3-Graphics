#include "ofApp.h"

void ofApp::reloadShaders()
{
	shadersNeedReload = false;
	terrainShader.load("shaders/terrain.vert", "shaders/terrain.frag");
}

//--------------------------------------------------------------
void ofApp::setup()
{
	reloadShaders();
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (shadersNeedReload) { reloadShaders(); }
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// drawing the terrain
	{
		// terrainShader.begin();
		// draw terrain
		// terrainShader.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case '`': shadersNeedReload = true;
			break;

		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key)
	{
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
