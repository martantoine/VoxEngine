#include "Camera.h"

namespace VoxEngine
{
	namespace VEEntity
	{

		//--------------------------------------------------------------------------------//
		//**********************************Constructors**********************************//
		//--------------------------------------------------------------------------------//
		Camera::Camera()
			: Pitch(0.0f), Yaw(0.0f), Roll(0.0f), GimbalLock(false)
		{
			m_lTranslation = glm::mat4(1.0f);
			InitVariables();
			SetProjection(90.0f, 1.0f);
			UpdateView();
		}

		Camera::Camera(glm::vec3 position)
			: Pitch(0.0f), Yaw(0.0f), Roll(0.0f), GimbalLock(false)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			InitVariables();
			SetProjection(90.0f, 1.0f);
			UpdateView();
		}

		Camera::Camera(float pitch, float yaw, float roll)
			: Pitch(pitch), Yaw(yaw), Roll(roll), GimbalLock(false)
		{
			m_lTranslation = glm::mat4(1.0f);
			InitVariables();
			SetProjection(90.0f, 1.0f);
			UpdateView();
		}

		Camera::Camera(glm::vec3 position, float pitch, float yaw, float roll)
			: Pitch(pitch), Yaw(yaw), Roll(roll), GimbalLock(false)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), position);
			InitVariables();
			SetProjection(90.0f, 1.0f);
			UpdateView();
		}

		Camera::Camera(float radius, float pitch, float yaw, float roll)
			: Pitch(pitch), Yaw(yaw), Roll(roll), Radius(radius), GimbalLock(true)
		{
			m_lTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			InitVariables();
			SetProjection(90.0f, 1.0f);
			UpdateView();
		}



		//-------------------------------------------------------------------------------//
		//**************************EntityComponent's functions**************************//
		//-------------------------------------------------------------------------------//
		void Camera::InitVariables()
		{
			m_EntityComponentType = EntityComponentType::MISC;

			MovingSpeed = 0.0002f;
			RotationgSpeed = 0.005f;
			ZoomSpeed = 0.1f;
			LastMousePosition = glm::vec2(0.0f, 0.0f);
			Center = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		
		void Camera::Reset()
		{
			Radius = 1.0f;
			Pitch = 0.0f;
			Yaw = 0.0f;
			Roll = 0.0f;
			Center = glm::vec3(0.0f, 0.0f, 0.0f);
			m_lTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			UpdateView();
		}

		void Camera::SetFOV(float fov)
		{
			FOV = fov;
			Projection = glm::perspective(glm::radians(fov), Ratio, 0.1f, 100.0f);
		}

		void Camera::SetProjection(float fov, float ratio)
		{
			FOV = fov;
			Ratio = ratio;
			Projection = glm::perspective(glm::radians(fov), Ratio, 0.1f, 100.0f);
		}

		void Camera::SetMousePos(glm::vec2 mousePosition)
		{
			offset = RotationgSpeed * (LastMousePosition - mousePosition);
			LastMousePosition = mousePosition;
		}

		void Camera::Move()
		{
			Center += Radius * (offset.x * Strafe + offset.y * glm::normalize(glm::cross(Strafe, Forward)));
		}

		void Camera::Move(glm::vec3 axis)
		{
			if (axis == glm::vec3(1, 0, 0))
				Position -= MovingSpeed * Strafe;
			else if (axis == glm::vec3(-1, 0, 0))
				Position += MovingSpeed * Strafe;

			else if (axis == glm::vec3(0, 0, 1))
				Position -= MovingSpeed * glm::normalize(glm::cross(Strafe, Forward));
			else if (axis == glm::vec3(0, 0, -1))
				Position += MovingSpeed * glm::normalize(glm::cross(Strafe, Forward));

			else if (axis == glm::vec3(0, 1, 0))
				Position -= MovingSpeed * Forward;
			else if (axis == glm::vec3(0, -1, 0))
				Position += MovingSpeed * Forward;
		}

		void Camera::Rotate()
		{
			Yaw -= offset.x;
			Pitch -= offset.y;
		}

		void Camera::Zoom(float zoomValue)
		{
			Radius += Radius * zoomValue * ZoomSpeed;
		}

		void Camera::UpdateView()
		{
			if (GimbalLock)
			{
				qPitch = angleAxis(Pitch, glm::vec3(1, 0, 0));
				qYaw = angleAxis(Yaw, glm::vec3(0, 0, 1));
				qRoll = angleAxis(Roll, glm::vec3(0, 0, 1));

				Orientation = qPitch * qYaw;
				Orientation = normalize(Orientation);

				Position = Center + static_cast<glm::vec3>(Radius * glm::vec4(0, 0, 1, 1) * glm::mat4_cast(Orientation));
			}
			else
			{
				qPitch = angleAxis(Pitch, glm::vec3(1, 0, 0));
				qYaw = angleAxis(Yaw, glm::vec3(0, 1, 0));
				qRoll = angleAxis(Roll, glm::vec3(0, 0, 1));

				Orientation = qPitch * qYaw;
				Orientation = normalize(Orientation);
			}

			m_lRotation = glm::mat4_cast(Orientation);
			m_lTranslation = translate(glm::mat4(1.0f), -Position);
			View = m_lRotation * m_lTranslation;

			Strafe = glm::vec3(View[0][0], View[1][0], View[2][0]);
			Forward = glm::vec3(View[0][2], View[1][2], View[2][2]);
		}

		glm::vec3 Camera::GetPosition()
		{
			return Position;
		}

		glm::mat4 Camera::GetView()
		{
			UpdateView();
			return View;
		}

		glm::mat4 Camera::GetProjection()
		{
			return Projection;
		}

	}
}