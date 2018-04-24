#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;


uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float mouseX;
uniform float mouseY;

uniform float screenHeight;
uniform float screenWidth;

out vec3 position;
flat out vec3 colour;

out vec2 ourUV;

out vec3 texcoord;

void main() {
	//position.x = vertex_position.x;
	//position.y = vertex_position.y;
	//position.z = vertex_position.z;

	position = vertex_position;
  	colour = vertex_colour;

 	texcoord = vec3(position.xyz);

  	gl_Position = projection * view  * model * vec4(vertex_position, 1.0f);	
}