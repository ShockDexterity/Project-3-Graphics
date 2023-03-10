#include "ofApp.h"
#include "buildTerrainMesh.h"
#include "CameraMatrices.h"

using namespace glm;

void ofApp::exit()
{
	terrainCells.stop();
}

void ofApp::reloadShaders()
{
	shadersNeedReload = false;
	terrainShader.load("shaders/terrain.vert", "shaders/terrain.frag");
	waterShader.load("shaders/water.vert", "shaders/water.frag");
}

void ofApp::updateCameraRotation(float dx, float dy)
{
	cameraHead -= dx;
	cameraPitch -= dy;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	glEnable(GL_CULL_FACE);

	heightmapLowRes.setUseTexture(false);
	heightmapLowRes.load("textures/TamrielLowRes.png");

	heightmapHighRes.setUseTexture(false);
	heightmapHighRes.load("textures/TamrielHighRes.png");

	assert(heightmapLowRes.getWidth() != 0 && heightmapLowRes.getHeight() != 0);
	assert(heightmapHighRes.getWidth() != 0 && heightmapHighRes.getHeight() != 0);

	const int lo_xEnd { static_cast<int>(heightmapLowRes.getWidth()) - 1 };
	const int lo_yEnd { static_cast<int>(heightmapLowRes.getHeight()) - 1 };
	const int hi_xEnd { static_cast<int>(heightmapHighRes.getWidth()) - 1 };
	const int hi_yEnd { static_cast<int>(heightmapHighRes.getHeight()) - 1 };

	float scale { hi_xEnd / static_cast<float>(lo_xEnd) };

	buildTerrainMesh(
		terrainMesh,
		heightmapLowRes,
		0,
		0,
		lo_xEnd,
		lo_yEnd,
		vec3(scale, 1600, scale)
	);

	const float waterHeight { 700.0f };
	waterMesh.addVertices({
		vec3(0,	waterHeight, 0),
		vec3(hi_xEnd, waterHeight, 0),
		vec3(hi_xEnd, waterHeight, hi_yEnd),
		vec3(0,	waterHeight, hi_yEnd),
		});

	waterMesh.addIndices(std::vector<ofIndexType>{ 0, 2, 1, 3, 2, 0 });

	camera.position = vec3(hi_xEnd * 0.5f, 1400, hi_yEnd * 0.5f);
	terrainCells.initializeForPosition(camera.position);

	ofSetBackgroundColor(136, 8, 8);
}

//--------------------------------------------------------------
void ofApp::update()
{
	// time since last frame
	const float dt { static_cast<float>(ofGetLastFrameTime()) };

	// update position
	camera.position += mat3(rotate(cameraHead, vY)) * velocity * dt;
	camera.rotation = rotate(cameraHead, vY) * rotate(cameraPitch, vX);

	terrainCells.optimizeForPosition(camera.position);

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
	const float resClip { 100.0f };
	CameraMatrices lo_camMatrices { camera, aspect, resClip, 10000.0f };
	CameraMatrices hi_camMatrices { camera, aspect, 1.0f, resClip };
	const mat4 model {};

	const mat4 lmv { lo_camMatrices.getView() * model };
	const mat4 lmvp { lo_camMatrices.getProj() * lmv };

	const mat4 hmv { hi_camMatrices.getView() * model };
	const mat4 hmvp { hi_camMatrices.getProj() * hmv };

	// drawing the terrain
	{
		terrainShader.begin();
		terrainShader.setUniform3f("meshColor", vec3(0.1f, 0.1f, 0.1f));
		terrainShader.setUniform3f("lightColor", vec3(1)); // white light
		terrainShader.setUniform3f("lightDir", normalize(vec3(1, 1, 1)));
		terrainShader.setUniform3f("ambientColor", vec3(0.1f));

		terrainShader.setUniformMatrix3f("normalMatrix", mat3(model));
		terrainShader.setUniformMatrix4f("mvp", lmvp);
		terrainShader.setUniformMatrix4f("mv", lmv);
		terrainMesh.draw();
		terrainShader.end();


		waterShader.begin();
		waterShader.setUniformMatrix4f("mvp", lmvp);
		waterMesh.draw();
		waterShader.end();
	}

	glClear(GL_DEPTH_BUFFER_BIT);

	{
		terrainShader.begin();
		terrainShader.setUniform3f("meshColor", vec3(0.1f, 0.1f, 0.1f));
		terrainShader.setUniform3f("lightColor", vec3(1)); // white light
		terrainShader.setUniform3f("lightDir", normalize(vec3(1, 1, 1)));
		terrainShader.setUniform3f("ambientColor", vec3(0.1f));

		terrainShader.setUniformMatrix3f("normalMatrix", mat3(model));
		terrainShader.setUniformMatrix4f("mvp", hmvp);
		terrainShader.setUniformMatrix4f("mv", hmv);
		terrainCells.drawActiveCells(camera.position, 500.0f);
		terrainShader.end();

		waterShader.begin();
		waterShader.setUniformMatrix4f("mvp", hmvp);
		waterMesh.draw();
		waterShader.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	const int vel { 250 };
	switch (key)
	{
		case '`': shadersNeedReload = true; break;

		case 'a': velocity.x = -vel; break;
		case 'A': velocity.x = -vel; break;
		case 'd': velocity.x = vel; break;
		case 'D': velocity.x = vel; break;

		case 'q': velocity.y = -vel; break;
		case 'Q': velocity.y = -vel; break;
		case 'e': velocity.y = vel; break;
		case 'E': velocity.y = vel; break;

		case 'w': velocity.z = -vel; break;
		case 'W': velocity.z = -vel; break;
		case 's': velocity.z = vel; break;
		case 'S': velocity.z = vel; break;

		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key)
	{
		case 'a': velocity.x = 0; break;
		case 'A': velocity.x = 0; break;
		case 'd': velocity.x = 0; break;
		case 'D': velocity.x = 0; break;

		case 'q': velocity.y = 0; break;
		case 'Q': velocity.y = 0; break;
		case 'e': velocity.y = 0; break;
		case 'E': velocity.y = 0; break;

		case 'w': velocity.z = 0; break;
		case 'W': velocity.z = 0; break;
		case 's': velocity.z = 0; break;
		case 'S': velocity.z = 0; break;

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
