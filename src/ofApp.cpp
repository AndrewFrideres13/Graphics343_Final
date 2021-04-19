#include "ofApp.h"
#include "GLFW/glfw3.h"
#include "CameraMatrices.h"
#include "SimpleDrawNode.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	using namespace glm;

	ofDisableArbTex();

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	ofEnableDepthTest();

	cubeMesh.load("models/cube.ply");

	cubemap.load("skyboxes/cube2_front.jpg", "skyboxes/cube2_back.jpg", "skyboxes/cube2_right.jpg", "skyboxes/cube2_left.jpg", "skyboxes/cube2_top.jpg", "skyboxes/cube2_bottom.jpg");

	cubemap.getTexture().generateMipmap();

	skyboxShader.load("skybox.vert", "skybox.frag");

	testSphere.load("models/sphere.ply");

	testShader.load("mesh.vert", "mesh.frag");

	sceneGraphRoot.childNodes.emplace_back(new SceneGraphNode());

	sceneGraphRoot.childNodes.back()->childNodes.emplace_back(new SimpleDrawNode(testSphere, testShader));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
	using namespace glm;

	float width = static_cast<float>(ofGetViewportWidth());
	float height = static_cast<float>(ofGetViewportHeight());
	float aspect = width / height;

	mat4 model;

	CameraMatrices camMatrices{ camera, aspect, 0.01f, 20.0f };

	skyboxShader.begin();

	glDepthFunc(GL_LEQUAL);

	skyboxShader.setUniformMatrix4f("mvp", camMatrices.getProj() * mat4(mat3(camMatrices.getView())));
	skyboxShader.setUniformTexture("cubemap", cubemap.getTexture(), 0);

	cubeMesh.draw();

	skyboxShader.end();
	glDepthFunc(GL_LESS);

	sceneGraphRoot.drawSceneGraph(camMatrices);

	/*
	testShader.begin();

	testSphere.draw();

	testShader.end();
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::drawCube(const CameraMatrices& camMatrices)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
