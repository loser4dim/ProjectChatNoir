#version 460 core

layout(location = 0) in vec3 vertex_position;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main(){
	gl_Position = projection_matrix * view_matrix * vec4(vertex_position, 1.0);

	return;
}