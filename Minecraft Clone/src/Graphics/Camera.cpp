#include "Camera.h"

#include <iostream>

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Constants.h"

Camera::Camera()
	:m_Roll(0.0f), m_Pitch(0.0f), m_Yaw(0.0f), m_FirstMouse(true), m_ViewMatrix(glm::mat4(1.0f)), m_ViewDirection(glm::vec3(0.0f, 0.0f, -1.0f)), m_LastMousePosition(glm::vec2(0.0f, 0.0f)), m_UP(glm::vec3(0.0f, 1.0f, 0.0f))
{
	m_Position = glm::vec3(0.0f, 0.0f, 2.0f);
	m_ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
}

Camera::~Camera()
{
}

void Camera::UpdateViewMatrix()
{
	glm::vec3 cameraLeft = glm::normalize(glm::cross(m_UP, m_ViewDirection));
	glm::mat4 rotator = glm::rotate(glm::radians(m_Yaw), m_UP) *
		glm::rotate(glm::radians(m_Pitch), cameraLeft);

	m_ViewDirection = glm::normalize(glm::mat3(rotator) * m_ViewDirection);
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ViewDirection, m_UP);
}

void Camera::ProcessMouseEvent(GLFWwindow* window)
{
	if (glfwGetWindowAttrib(window, GLFW_HOVERED)) {

		double xPos = 0, yPos = 0;
		glfwGetCursorPos(window, &xPos, &yPos);
		if (m_FirstMouse) {
			m_LastMousePosition.x = xPos;
			m_LastMousePosition.y = yPos;
			m_FirstMouse = false;
		}


		float dx = xPos - m_LastMousePosition.x;
		float dy = yPos - m_LastMousePosition.y;

		m_LastMousePosition = { xPos, yPos };

		float sensitivity = 0.05f;
		dx *= sensitivity;
		dy *= sensitivity;

		m_Yaw = -dx;
		m_Pitch = dy;

		// Clamp pitch to avoid flipping
		if (m_Pitch > 89.0f) {
			m_Pitch = 89.0f;
		}
		if (m_Pitch < -89.0f) {
			m_Pitch = -89.0f;
		}

	}
	else {
		m_Pitch = 0;
		m_Yaw = 0;
		m_FirstMouse = true;
	}
}

void Camera::ProcessKeyboardEvents(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_Position += m_CameraSpeed * m_ViewDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		glm::vec3 leftDirection = glm::normalize(glm::cross(m_UP, m_ViewDirection));
		m_Position += m_CameraSpeed * leftDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_Position += -m_CameraSpeed * m_ViewDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		glm::vec3 rightDirection = -glm::normalize(glm::cross(m_UP, m_ViewDirection));
		m_Position += m_CameraSpeed * rightDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		m_Position += m_CameraSpeed * m_UP;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		m_Position += -m_CameraSpeed * m_UP;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		m_CameraSpeed = 0.25f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
		m_CameraSpeed = 0.09f;
	}
}

void Camera::Update()
{
	UpdateViewMatrix();
}
