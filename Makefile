CFLAGS = -std=c++17 -O3
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
SRCS = main.cpp loader.cpp utils.cpp key_input.cpp load_img.cpp Vulkan_app.cpp model_loading.cpp texture_loading.cpp pipeline.cpp app_init.cpp command.cpp

VulkanTest: $(SRCS)
	g++ $(CFLAGS) -o VulkanTest $(SRCS) $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest