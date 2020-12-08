#include "Camera3D.h"

namespace NTCrystal{


	Camera3D::Camera3D() :
		m_position(0.0f, 0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthoMatrix(1.0f),
		m_scale(1.0f),
		m_needsMatrixUpdate(true),
		m_screenWidth(500),
		m_screenHeight(500),
		m_movmentSpeedFactor(1.0f),
		m_pitchSensitivity(1.0f),
		m_yawSensitivity(1.0f),
		m_rotation(0.0f, 1.0f, 0.0f),
		m_speed(1.0f)
	{

	}

	void Camera3D::update(){
		if (m_needsMatrixUpdate){
				
		}
	}

	


}