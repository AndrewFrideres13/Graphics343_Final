#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "SceneGraphNode.h"
#include "ofxCubemap.h"
#include "CameraMatrices.h"
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "cameraT.h"
#include "material.h"

class ofApp : public ofBaseApp{

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

	private:
		ofShader testShader;
		ofShader skyboxShader;
		ofMesh testSphere;
		ofMesh cubeMesh;
		ofxCubemap cubemap;

		ofImage img; // Image object to be saved
		int imgWidth = 600; // Width of image (height is calculated in setup)
		float aspectRatio = 3.0f / 2.0f; // Aspect ratio of image

		SceneGraphNode sceneGraphRoot;
		std::shared_ptr<SceneGraphNode> sphereNode;

		void drawCube(const CameraMatrices& camMatrices);

		Camera camera{ glm::vec3(0, 1.0f, 10.0f) };

		vec3T firstV;
		vec3T secondV;
		vec3T thirdV;
		
};
