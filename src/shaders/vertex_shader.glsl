#version 400
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

uniform float time;
uniform mat4 rotationMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float mouseX;
uniform float mouseY;
uniform float screenHeight;
uniform float screenWidth;
uniform float rotValueUniform;

out vec3 position;
out vec3 colour;
void main() {
	position.x = vertex_position.x;
	position.y = vertex_position.y;
	position.z = vertex_position.z;
  	colour = vertex_colour;


  	gl_Position = projection * view  * model * vec4(position, 1.0f);	
  
}