#include "Vulkan_App.hpp"
#include "utils.hpp"

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