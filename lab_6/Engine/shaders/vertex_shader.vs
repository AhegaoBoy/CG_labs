#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;  // Передаём цвет во фрагментный шейдер

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * vec4(position, 1.0);  // Трансформация позиции
    vertexColor = color;  // Передаём цвет
}