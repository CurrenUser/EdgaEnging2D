#version 460 core
layout (location = 0) in vec3 position;
uniform float size;
void main() {
gl_Position = vec4(size * position.x, size * position.y, size * position.z, 1.0);
}