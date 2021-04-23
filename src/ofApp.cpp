#include "ofApp.h"
#include "GLFW/glfw3.h"
#include "CameraMatrices.h"
#include "SimpleDrawNode.h"

float hit_sphere(const point3& center, float radius, const ray& r) {
	vec3T oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0f * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1.0f;
	}
	else 
	{
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}

color ray_color(const ray& r)
{
	auto t = hit_sphere(point3(0, 0, -1), 0.5f, r);
	if (t > 0.0f) {
		vec3T N = unit_vector(r.at(t) - vec3T(0, 0, -1));
		return 0.5f * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3T unit_direction = unit_vector(r.direction());
	t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

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

	int imgHeight = (int)(imgWidth / aspectRatio); // Setting height based on aspect ratio

	float viewport_height = 2.0f; // Setting up the viewport for raytracing
	float viewport_width = aspectRatio * viewport_height;
	float focal_length = 1.0f;

	point3 origin = point3(0, 0, 0); // Origin of the camera
	auto horizontal = vec3T(viewport_width, 0, 0);
	auto vertical = vec3T(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3T(0, 0, focal_length);

	img.allocate(imgWidth, imgHeight, OF_IMAGE_COLOR);
	img.setColor(ofColor::white);

	for (int j = imgHeight - 1; j >= 0; j--) {
		for (int i = 0; i < imgWidth; i++) {
			auto u = float(i) / (imgWidth - 1);
			auto v = float(j) / (imgHeight - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r);
			ofColor color(pixel_color.x() * 255, pixel_color.y() * 255, pixel_color.z() * 255);
			//ofColor color(255, 0, 0);
			img.setColor(i % imgWidth, ((imgHeight - 1) - j) % imgHeight, color);
		}
	}

	//for (int i = 0; i < imgWidth; i++) {
	//	for (int j = 0; j < imgHeight; j++) {
	//		ofColor color = ofColor(255 - i % imgWidth, j % imgHeight, 255);
	//		img.setColor(i % imgWidth, j % imgHeight, color);
	//	}
	//}

	img.update();
	img.save("Pixels.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
	using namespace glm;

	/*
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
	*/

	/*
	testShader.begin();

	testSphere.draw();

	testShader.end();
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') 
	{
		img.grabScreen(0, 0, 1000, 1000);

		img.save("Raycast.jpg");
	}
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
