#include "ofApp.h"
#include "GLFW/glfw3.h"
#include "CameraMatrices.h"
#include "SimpleDrawNode.h"

/*
float hit_sphere(const point3& center, float radius, const ray& r) {
	vec3T oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) 
	{
		return -1.0f;
	}
	else 
	{
		return (-half_b - sqrt(discriminant)) / (a);
	}
}
*/

color ray_color(const ray& r, const hittable& world, int depth)
{
	if (depth <= 0) {
		return color(0, 0, 0);
	}

	hit_record rec;
	if (world.hit(r, 0.001f, infinity, rec)) {
		//point3 target = rec.p + rec.normal + random_unit_vector();
		//point3 target = rec.p + random_in_hemisphere(rec.normal);
		//return 0.5f * ray_color(ray(rec.p, target - rec.p), world, depth - 1);

		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) 
		{
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		return color(0, 0, 0);
	}
	vec3T unit_direction = unit_vector(r.direction());
	auto t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

hittable_list random_scene() {
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5f, 0.5f, 0.5f));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_float();
			point3 center(a + 0.9f * random_float(), 0.2f, b + 0.9f * random_float());

			if ((center - point3(4, 0.2f, 0)).length() > 0.9f) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8f) 
				{
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2f, sphere_material));
				}
				else if (choose_mat < 0.95f) 
				{
					auto albedo = color::random(0.5f, 1);
					auto fuzz = random_float(0, 0.5f);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2f, sphere_material));
				}
				else 
				{
					sphere_material = make_shared<dielectric>(1.5f);
					world.add(make_shared<sphere>(center, 0.2f, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5f);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0f, material1));

	auto material2 = make_shared<lambertian>(color(0.4f, 0.2f, 0.1f));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0f, material2));

	auto material3 = make_shared<metal>(color(0.7f, 0.6f, 0.5f), 0.0f);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0f, material3));

	return world;
}

hittable_list rainbow() 
{
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5f, 0.5f, 0.5f));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	auto redMetal = make_shared<metal>(color(1.0f, 0.0f, 0.0f), 0.0f);
	auto orangeMetal = make_shared<metal>(color(1.0f, 0.65f, 0.0f), 0.1f);
	auto yellowMetal = make_shared<metal>(color(1.0f, 1.0f, 0.0f), 0.2f);
	auto greenMetal = make_shared<metal>(color(0.0f, 0.5f, 0.0f), 0.3f);
	auto blueMetal = make_shared<metal>(color(0.0f, 0.0f, 1.0f), 0.4f);
	auto purpleMetal = make_shared<metal>(color(0.29f, 0.0f, 0.51f), 0.5f);
	auto violetMetal = make_shared<metal>(color(0.93f, 0.51f, 0.93f), 0.6f);
	auto pureMetal = make_shared<metal>(color(0.7f, 0.6f, 0.5f), 0.0f);

	world.add(make_shared<sphere>(point3(-4.5f, 0.5f, -1.0f), 0.5f, redMetal));
	world.add(make_shared<sphere>(point3(-3.0f, 1.5f, -1.0f), 0.5f, orangeMetal));
	world.add(make_shared<sphere>(point3(-1.5f, 2.25f, -1.0f), 0.5f, yellowMetal));
	world.add(make_shared<sphere>(point3(0.0f, 2.75f, -1.0f), 0.5f, greenMetal));
	world.add(make_shared<sphere>(point3(1.5f, 2.25f, -1.0f), 0.5f, blueMetal));
	world.add(make_shared<sphere>(point3(3.0f, 1.5f, -1.0f), 0.5f, purpleMetal));
	world.add(make_shared<sphere>(point3(4.5f, 0.5f, -1.0f), 0.5f, violetMetal));
	world.add(make_shared<sphere>(point3(0.0f, 1.0f, -1.0f), 1.0f, pureMetal));

	return world;
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

	// RAYTRACING STUFF BEGINS
	const int imgHeight = (int)(imgWidth / aspectRatio); // Setting height based on aspect ratio
	const int samples_per_pixel = 2;
	const int max_depth = 10;

	// World setup
	auto R = cos(piT / 4);
	auto world = rainbow(); // Creating all the objects in the scene

	//auto material_ground = make_shared<lambertian>(color(0.8f, 0.8f, 0.0f));
	//auto material_center = make_shared<lambertian>(color(0.1f, 0.2f, 0.5f));
	//auto material_left = make_shared<dielectric>(1.5f);
	//auto material_right = make_shared<metal>(color(0.8f, 0.6f, 0.2f), 0.0f);

	//world.add(make_shared<sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
	//world.add(make_shared<sphere>(point3(0.0f, 0.0f, -1.0f), 0.5f, material_center));
	//world.add(make_shared<sphere>(point3(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
	//world.add(make_shared<sphere>(point3(-1.0f, 0.0f, -1.0f), -0.45f, material_left));
	//world.add(make_shared<sphere>(point3(1.0f, 0.0f, -1.0f), 0.5f, material_right));

	// Camera setup
	point3 lookfrom(4, 2, 8);
	point3 lookat(1, 2, 0);
	vec3T vup(0, 1, 0);
	auto dist_to_focus = 10.0f;
	auto aperture = 0.1f;
	cameraT cam(lookfrom, lookat, vup, 40, aspectRatio, aperture, dist_to_focus);

	// Image setup
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
