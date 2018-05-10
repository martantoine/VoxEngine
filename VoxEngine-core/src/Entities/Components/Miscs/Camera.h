#pragma once

#include "../EntityComponent.h"
#include <glm\gtx\transform.hpp>
#include <GLM\gtx\quaternion.hpp>
#include <GLM\gtc\quaternion.hpp>
#include <GLM\glm.hpp>

namespace UE
{
	namespace UEntity
	{

		class Camera : public EntityComponent
		{
		public:
			//Constructors
			Camera();
			Camera(glm::vec3 position);
			Camera(float pitch, float yaw, float roll);
			Camera(glm::vec3 position, float pitch, float yaw, float roll);
			Camera(float radius, float pitch, float yaw, float roll, glm::vec3 center);

			//EntityComponent's functions
			void InitVariables();
			void Reset();
			void SetFOV(float fov);
			void SetProjection(float fov, float ratio);

			//Transforming the camera
			void SetMousePos(glm::vec2 mousePosition);
			void Move();
			void Move(glm::vec3 axis);
			void Rotate();
			void Zoom(float zoomValue);
			void UpdateView();
			glm::vec3 GetPosition();
			glm::mat4 GetView();
			glm::mat4 GetProjection();

		private:
			bool GimbalLock;
			float Pitch, Roll, Yaw;
			float Radius;
			float FOV, Ratio;
			float ZoomSpeed, RotationgSpeed, MovingSpeed;
			glm::vec2 offsetProj;

			glm::vec2 LastMousePosition, offset;
			glm::vec3 Forward, Strafe, Center, Position;
			glm::quat Orientation, qPitch, qRoll, qYaw; 
			glm::mat4 View, Projection;
		};

	}
}