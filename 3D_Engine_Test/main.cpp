#include <Window.h>
#include <NTCrystal.h>
#include <glew.h>
#include <freeglut.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <Shader.h>
#include <mat4.h>
#include <Buffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderable2D.h>
#include <Simple2DRenderer.h>
#include <BatchRenderer2D.h>
#include <Sprite.h>
#include <time.h>
#include <Timmer.h>

using namespace NTCrystal;
using namespace Graphics;
using namespace math;

int main(int argc, char **argv){
	
	NTCrystal::init();
	NTCrystal::Window m_window;
	m_window.create("3D Game Engine testing platform" , 1280, 960, NULL);
	
	mat4 ortho = NTCrystal::math::mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("test.vert", "test.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniform4f("color_uniform", vec4(0.5f, 0.5f, 0.0f, 1.0f));

	srand(time(NULL));

	std::vector<Renderable2D*> sprites;
	Sprite sprite(vec3(5.0f, 5.0f, 0.0f), vec2(4.0f, 4.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f));
	

	for (float y = 0; y < 18.0f; y += 0.08f)
	{
		for (float x = 0; x < 18.0f; x += 0.08f)
		{
			sprites.push_back(new Sprite(vec3(x, y, 0), vec2(0.08f, 0.08f), 
				vec4((rand() % 1000 / 1000.f), (rand() % 1000 / 1000.f), (rand() % 1000 / 1000.f), 1.0f)));
		}
	}

	BatchRenderer2D renderer;



	Timmer timer;
	while (!m_window.closed()){
		timer.reset();
		m_window.clear();
		
		vec2 mousePosition = m_window.getMousePos();
		shader.setUniform2f("light_position", vec2(
			(mousePosition.x * 16.0f / 1280.0f), 
			(9.0f - mousePosition.y * 9.0f / 960.0f)));
		renderer.begin();

		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
		renderer.end();
		renderer.flush();
		m_window.update();

		if (m_window.isKeyPressed(GLFW_KEY_ESCAPE)){
			m_window.~Window();
		}
		printf("%f ms Sprite count: %i\n", timer.elapsed(), sprites.size());
	}
	
	return 0;
}
