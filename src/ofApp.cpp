#include "ofApp.h"
#include "GLFW/glfw3.h"
#include <chrono>
using namespace std::chrono;
using namespace glm;
color ray_color(const ray& r, const hittable& world, int depth) {
	if (depth <= 0) {
		return color(0, 0, 0);
	}

	hit_record rec;
	if (world.hit(r, 0.001f, infinity, rec)) {
		//point3 target = rec.p + rec.normal + random_unit_vector();
		point3 target = rec.p + random_in_hemisphere(rec.normal);
		return 0.5f * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
	}
	vec3T unit_direction = unit_vector(r.direction());
	auto t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofDisableArbTex();

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	ofEnableDepthTest();

	const int imgHeight = (int)(imgWidth / aspectRatio); // Setting height based on aspect ratio
	const int samples_per_pixel = 10;
	const int max_depth = 10;

	hittable_list world; // Creating all the objects in the scene
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5f));
	world.add(make_shared<sphere>(point3(0, -100.5f, -1), 100));

	cameraT cam;

	//Start our high precision timer before we begin the raytracing work
	auto start = high_resolution_clock::now();

	img.allocate(imgWidth, imgHeight, OF_IMAGE_COLOR);
	img.setColor(ofColor::white);

	for (int j = imgHeight - 1; j >= 0; j--) {
		for (int i = 0; i < imgWidth; i++) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++) {
				auto u = (i + random_float()) / (imgWidth - 1);
				auto v = (j + random_float()) / (imgHeight - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}

			//auto u = float(i) / (imgWidth - 1);
			//auto v = float(j) / (imgHeight - 1);
			//ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			//color pixel_color = ray_color(r, world);
			auto rColor = sqrt(pixel_color.x() / samples_per_pixel);
			auto gColor = sqrt(pixel_color.y() / samples_per_pixel);
			auto bColor = sqrt(pixel_color.z() / samples_per_pixel);
			rColor = 256 * clamp(rColor, 0.0f, 0.999f);
			gColor = 256 * clamp(gColor, 0.0f, 0.999f);
			bColor = 256 * clamp(bColor, 0.0f, 0.999f);
			ofColor color(rColor, gColor, bColor);
			//ofColor color(255, 0, 0);
			img.setColor(i % imgWidth, ((imgHeight - 1) - j) % imgHeight, color);
		}
	}

	img.update();
	img.save("Pixels.jpg");

	//Stop our timer, and calculate the elapsed time
	//This may need to move before we save the img...not 100% sure yet.
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "\nElapsed Time: " << duration.count() << "ms" << std::endl;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's') {
		img.grabScreen(0, 0, 1000, 1000);

		img.save("Raycast.jpg");
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
