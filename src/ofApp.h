#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "SceneGraphNode.h"
#include "ofxCubemap.h"
#include "CameraMatrices.h"
#include "Raytracer/Tracer.h"

class ofApp : public ofBaseApp {

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
	ofShader testShader;
	ofShader skyboxShader;
	ofMesh testSphere;
	ofMesh cubeMesh;
	ofxCubemap cubemap;

	SceneGraphNode sceneGraphRoot;
	std::shared_ptr<SceneGraphNode> sphereNode;

	void drawCube(const CameraMatrices& camMatrices);

	Camera camera{ glm::vec3(0, 1.0f, 10.0f) };

	ofImage rayTracedImage;
	Ray rayTracer{};
};
