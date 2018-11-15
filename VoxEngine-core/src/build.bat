emcc -I"main.cpp" "Entities/Entity.cpp" "Entities/Components/EntityComponent.cpp" "Entities/Components/Lights/PointLight.cpp" "Entities/Components/Miscs/Camera.cpp" "Entities/Components/Renderable/Renderable.cpp" "Entities/Components/Renderable/Shapes/Rectangle.cpp" "Graphics/Window.cpp" "Graphics/Buffers/EBO.cpp" "Graphics/Buffers/Texture.cpp" "Graphics/Buffers/VAO.cpp" "Graphics/Buffers/VBO.cpp" "Graphics/Renderers/SimpleRenderer2D.cpp" "Graphics/Shaders/Shader.cpp" "Graphics/Shaders/LightingShader.cpp" "../../Dependencies/GLM/include/GLM/glm.hpp" "../../Dependencies/GLM/include/GLM/vec2.hpp" "../../Dependencies/GLM/include/GLM/vec3.hpp" -I"../../Dependencies/GLM/include/GLM/vec4.hpp" "../../Dependencies/GLM/include/GLM/mat4x4.hpp" -s USE_GLFW=3 -s LEGACY_GL_EMULATION=1 --memory-init-file 0 -o index.html