#include "ofApp.h"
#include "GLFW/glfw3.h"
#include "CameraMatrices.h"
#include "SimpleDrawNode.h"

//--------------------------------------------------------------
void ofApp::setup() {
	using namespace glm;

	//ofDisableArbTex();

	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	//ofEnableDepthTest();

	/*cubeMesh.load("models/cube.ply");

	cubemap.load("skyboxes/cube2_front.jpg", "skyboxes/cube2_back.jpg", "skyboxes/cube2_right.jpg", "skyboxes/cube2_left.jpg", "skyboxes/cube2_top.jpg", "skyboxes/cube2_bottom.jpg");

	cubemap.getTexture().generateMipmap();

	skyboxShader.load("skybox.vert", "skybox.frag");

	testSphere.load("models/sphere.ply");

	testShader.load("mesh.vert", "mesh.frag");

	sceneGraphRoot.childNodes.emplace_back(new SceneGraphNode());

	sceneGraphRoot.childNodes.back()->childNodes.emplace_back(new SimpleDrawNode(testSphere, testShader));
	*/
	//Disabled above for time being for img testing/saving purposes


}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	using namespace glm;

	//Getting our screen w,h, & aspect ratio
	float width = static_cast<float>(ofGetViewportWidth());
	float height = static_cast<float>(ofGetViewportHeight());
	float aspect = width / height;

	//Setting our origin pt
	vec3 origin = vec3(0.0f, 0.0f, 0.0f);

	//Drawing a circle, filling it to prove saving an img to file is working
	ofSetColor(255, 130, 0);
	ofFill();
	ofDrawCircle(25, 100, 50);

	/*mat4 model;

	CameraMatrices camMatrices{ camera, aspect, 0.01f, 20.0f };

	skyboxShader.begin();

	glDepthFunc(GL_LEQUAL);

	skyboxShader.setUniformMatrix4f("mvp", camMatrices.getProj() * mat4(mat3(camMatrices.getView())));
	skyboxShader.setUniformTexture("cubemap", cubemap.getTexture(), 0);

	cubeMesh.draw();

	skyboxShader.end();
	glDepthFunc(GL_LESS);

	sceneGraphRoot.drawSceneGraph(camMatrices);


	testShader.begin();

	testSphere.draw();

	testShader.end();
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's') {
		//
		//Sanity check in our logs to show we are taking a screenshot
		//Defaults to bin/data folder (hangs out with the frag/vert shaders)
		//
		//*******WILL override image if there is an existing one*******
		std::cout << "Screenshot of Scene Taken!" << std::endl;
		//Saves image on s key press, need to grab screen, then save it as such
		rayTracedImage.grabScreen(0, 0, 300, 300);
		rayTracedImage.save("test.jpg", OF_IMAGE_QUALITY_BEST);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::drawCube(const CameraMatrices& camMatrices) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
