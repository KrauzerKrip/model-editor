#pragma once 

#include <glm/glm.hpp>

class Camera {
public:
	Camera();
	~Camera();
	
	glm::mat4 getViewMatrix();
	/*glm::mat4 getModelMatrix();*/
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	//glm::vec3 getRotation();
	//void setRotation(glm::vec3 rotation);
	void setDirection(glm::vec3 direction);
	glm::vec3 getCameraFront();
	glm::vec3 getCameraRight();

private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraRight;
};
