#include "Vulkan_App.hpp"
#include "utils.hpp"

void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		trans_text *= -1;
}

float degToRadians(float angle) {
	return (angle * (3.14159265 / 180));
}


int main() {
    Vulkan_App app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}