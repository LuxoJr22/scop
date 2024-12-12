#include "utils.hpp"

void keyboard_input(GLFWwindow  *window, vector3 *position)
{
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