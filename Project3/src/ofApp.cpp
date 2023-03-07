#include "ofApp.h"
#include "buildTerrainMesh.h"

using namespace glm;

void ofApp::reloadShaders()
{
	shadersNeedReload = false;
	terrainShader.load("shaders/terrain.vert", "shaders/terrain.frag");
}

void ofApp::updateCameraRotation(float dx, float dy)
{
	cameraHead += dx;
	cameraPitch += dy;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();
	ofEnableDepthTest();

	glEnable(GL_CULL_FACE);

	ofShortImage heightmap {};
	heightmap.setUseTexture(false);
	heightmap.load("textures/TamrielLowRes.png");
	assert(heightmap.getWidth() != 0 && heightmap.getHeight() != 0);

	buildTerrainMesh(
		terrainMesh,
		heightmap,
		0,
		0,
		heightmap.getWidth() - 1,
		heightmap.getHeight() - 1,
		vec3(1, 50, 1)
	);

	for (size_t i = 0; i < terrainMesh.getNumNormals(); i++)
	{
		terrainMesh.setNormal(i, -terrainMesh.getNormal(i));
	}
	terrainMesh.flatNormals();
}

//--------------------------------------------------------------
void ofApp::update()
{
	// time since last frame
	const float dt { static_cast<float>(ofGetLastFrameTime()) };

	// Grabbing the current window
	// auto window { ofGetCurrentWindow() };

	// calculate world space velocity
	const mat3 mCamHead { mat3(rotate(-cameraHead, vY)) };
	const mat3 mCamPitch { mat3(rotate(-cameraPitch, vX)) };

	// update position
	position += (mCamHead * mCamPitch) * velocity * dt;

	if (shadersNeedReload) { reloadShaders(); }
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// finding the aspect ratio of the viewport
	const float width { static_cast<float>(ofGetViewportWidth()) };
	const float height { static_cast<float>(ofGetViewportHeight()) };
	const float aspect { width / height };

	// constant view and projection for the models
	const mat4 view { (rotate(cameraPitch, vX) * rotate(cameraHead, vY)) * translate(-position) };
	const mat4 proj { perspective(radians(100.0f), aspect, 1.0f, 1000.0f) };
	const mat4 model {};


	// drawing the terrain
	terrainShader.begin();
	{
		terrainShader.setUniformMatrix3f("normalMatrix", mat3(model));
		terrainShader.setUniformMatrix4f("mvp", proj * view * model);
		terrainShader.setUniformMatrix4f("mv", view * model);
		terrainShader.setUniform3f("meshColor", vec3(0.9f, 0.4f, 0.8f));
		terrainShader.setUniform3f("lightColor", vec3(1)); // white light
		terrainShader.setUniform3f("lightDir", normalize(vec3(-1, 1, 1)));
		terrainShader.setUniform3f("ambientColor", vec3(0.1));
		terrainMesh.draw();
	}
	terrainShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case '`': shadersNeedReload = true; break;

		case 'a': velocity.x = -10; break;
		case 'd': velocity.x = 10; break;

		case 'q': velocity.y = -10; break;
		case 'e': velocity.y = 10; break;

		case 'w': velocity.z = -10; break;
		case 's': velocity.z = 10; break;

		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key)
	{
		case 'a': velocity.x = 0; break;
		case 'd': velocity.x = 0; break;

		case 'q': velocity.y = 0; break;
		case 'e': velocity.y = 0; break;

		case 'w': velocity.z = 0; break;
		case 's': velocity.z = 0; break;
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	if (prevX != 0 && prevY != 0)
	{
		//update camera rotation based on mouse movement
		updateCameraRotation(mouseSensitivity * (x - prevX), mouseSensitivity * (y - prevY));
	}

	//remember where the mouse was this frame
	prevX = x;
	prevY = y;
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
