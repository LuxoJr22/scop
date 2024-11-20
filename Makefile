CFLAGS = -std=c++17 -O3
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTest: main.cpp loader.cpp utils.cpp key_input.cpp load_img.cpp
	g++ $(CFLAGS) -o VulkanTest main.cpp loader.cpp utils.cpp key_input.cpp load_img.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest