#include "ofApp.h"
#include "GLFW/glfw3.h"
#include "CameraMatrices.h"
#include "SimpleDrawNode.h"
#include <chrono>
using namespace std::chrono;
//--------------------------------------------------------------

void ofApp::setup() {
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


	// Image
	const auto aspect_ratio = imgHeight / imgWidth;

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = vec3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	img.allocate(imgWidth, imgHeight, OF_IMAGE_COLOR);
	img.setColor(ofColor::white);

	//Start our high precision timer before we begin the brunt of the raytracing work
	auto start = high_resolution_clock::now();

	for (int i = 0; i < imgWidth; i++) {
		for (int j = 0; j < imgHeight; j++) {
			auto u = float(i) / (imgWidth - 1);
			auto v = float(j) / (imgHeight - 1);
			tracer = { origin, lower_left_corner + u * horizontal + v * vertical - origin };
			vec3 pixel_color = tracer.ray_color(tracer);
			//ofColor color = ofColor(255 - i % imgWidth, j % imgHeight, 255);
			//ofColor color = ofColor(pixel_color.r - i % imgWidth, pixel_color.g - j % imgHeight, pixel_color.b);
			ofColor color(pixel_color.x * 255, pixel_color.y * 255, pixel_color.z * 255);
			img.setColor(i % imgWidth, j % imgHeight, color);
		}
	}

	//Stop our timer, and calculate the elapsed time
	//This may need to move to after we save the img...not 100% sure yet.
	//Mainly, we want to record the brunt of the work which will be the 
	//function above, and any other intensive calculations done.
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "Elapsed Time: " << duration.count() << "ms" << std::endl;

	img.update();
	img.save("Pixels.jpg");


}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
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
void ofApp::keyPressed(int key) {

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
