#pragma once

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class Camera
{
public:
	Camera();
	~Camera();


	void ProcessMouseEvent(GLFWwindow* window);
	void ProcessKeyboardEvents(GLFWwindow* window);
	void Update();

	inline glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline glm::vec3 GetCameraPosition() const { return m_Position; }
private:
	float m_CameraSpeed = 0.9f; // TODO: Compensate for delta time

	float m_Roll;  // Rotation around view direction axis
	float m_Pitch; // Rotation around camera's left direction axis (for moving the camera up or down)
	float m_Yaw;   // Rotation around camera's up direcion axis (for moving the camera left or right)

	bool m_FirstMouse;
	glm::vec2 m_LastMousePosition;
	glm::vec3 m_Position;
	glm::vec3 m_ViewDirection;
	const glm::vec3 m_UP;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
private:
	void UpdateViewMatrix();
};

