#include "utils.hpp"

void keyboard_input(GLFWwindow  *window, vector3 *position, vector3 *c_pos)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			c_pos->x -= 0.01;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			c_pos->x += 0.01;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			c_pos->z += 0.01;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			c_pos->z -= 0.01;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			c_pos->y -= 0.01;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			c_pos->y += 0.01;
		
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			c_pos->x = 5.f;
			c_pos->y = 0.f;
			c_pos->z = 0.f;
			position->x = 0.f;
			position->y = 0.f;
			position->z = 0.f;
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position->x -= 0.01;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position->x += 0.01;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position->z += 0.01;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position->z -= 0.01;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			position->y -= 0.01;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			position->y += 0.01;
	}
}