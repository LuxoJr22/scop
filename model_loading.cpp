#include "Vulkan_App.hpp"

void Vulkan_App::loadModel(const char * model_path, std::vector<Vertex>& verti, std::unordered_map<Vertex, uint32_t>& uniqueVert, std::vector<uint32_t>& ind) {
	attributes att;

	Load_obj(&att, model_path);

	center_obj(&att);


	for (const auto& faces : att.faces) {
		fill_indices(faces.tris[0], att, verti, uniqueVert, ind);
		if (faces.isTriangle == false)
			fill_indices(faces.tris[1], att, verti, uniqueVert, ind);
	}
}

void Vulkan_App::fill_indices(const float tris[3], attributes att, std::vector<Vertex>& verti, std::unordered_map<Vertex, uint32_t>& uniqueVert, std::vector<uint32_t>& ind)
{
	float width = att.lim_x.max - att.lim_y.min;
	float height = att.lim_y.max - att.lim_y.min;
	float thickness = att.lim_z.max - att.lim_z.min;
	float color = float((rand() % 80)) / 100.0f;

	float totalw = (width * 2) + (thickness * 2);

	for (int i = 0; i < 3; i ++)
	{
		Vertex vertex{};
		vert verte = att.vertices[tris[i]];

		vertex.pos = {
			verte.x,
			verte.y,
			verte.z
		};

		float x_coord = 1 - (verte.x + (width / 2)) / (width);
		float y_coord = 1 - (verte.y + (height / 2)) / (height);
		float z_coord = 1 - (verte.z + (thickness / 2)) / (thickness);

		float offw = totalw - (z_coord * thickness) - ((x_coord * width) + (z_coord * thickness));

		vertex.texCoord = {
			offw / totalw,
			y_coord
		};

		vertex.color = {color, .0f, .0f};

		if (uniqueVert.count(vertex) == 0) {
			uniqueVert[vertex] = static_cast<uint32_t>(verti.size());
			verti.push_back(vertex);
		}
				
		ind.push_back(uniqueVert[vertex]);
	}
}

void Vulkan_App::createVertexBuffer(std::vector<Vertex>& vert, VkBuffer& vertBuffer, VkDeviceMemory& vertBufferMemory) {
	VkDeviceSize bufferSize = sizeof(vert[0]) * vert.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vert.data(), (size_t) bufferSize);
	vkUnmapMemory(device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertBuffer, vertBufferMemory);

	copyBuffer(stagingBuffer, vertBuffer, bufferSize);
	
	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void Vulkan_App::createIndexBuffer(std::vector<uint32_t> ind, VkBuffer& indBuffer, VkDeviceMemory& indBufferMemory) {
	VkDeviceSize bufferSize = sizeof(ind[0]) * ind.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, ind.data(), (size_t) bufferSize);
	vkUnmapMemory(device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indBuffer, indBufferMemory);

	copyBuffer(stagingBuffer, indBuffer, bufferSize);

	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void Vulkan_App::createUniformBuffers(std::vector<VkBuffer> &uniform_buffers, std::vector<void*> &uniform_buffersMapped, std::vector<VkDeviceMemory> &uniform_buffersMemory) {
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	uniform_buffers.resize(MAX_FRAMES_IN_FLIGHT);
	uniform_buffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
	uniform_buffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniform_buffers[i], uniform_buffersMemory[i]);

		vkMapMemory(device, uniform_buffersMemory[i], 0, bufferSize, 0, &uniform_buffersMapped[i]);
	}
}