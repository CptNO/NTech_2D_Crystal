#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace NTCrystal{

	class Camera3D
	{
	public:
		Camera3D();
		~Camera3D();

		void init(int screenWidth, int screenHeight);

		void translateCameraToWindowCoordinates(glm::vec3 &coords);

		void update();

		glm::vec3 getPosition() { return m_position; }
		float getScale() { return m_scale; }
		glm::mat4 getCamreaMatrix() { return m_cameraMatrix; }
		glm::vec3 getRotation() { return m_rotation; }


	private:
		
		int m_screenWidth, m_screenHeight;
		bool m_needsMatrixUpdate;
		float m_scale;
		float m_movmentSpeedFactor;
		float m_pitchSensitivity;
		float m_yawSensitivity;


		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_speed;

	
		glm::mat4 m_modelView;
		glm::mat4 m_projectionView;

		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;

		
		

	};

	Camera3D::Camera3D()
	{
	}

	Camera3D::~Camera3D()
	{
	}

}