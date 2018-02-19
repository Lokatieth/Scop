#version 400
in vec3 colour;
in vec3 position;
out vec4 frag_colour;

precision mediump float;
uniform vec4 ourColour;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {
  //vec2 pos = ( gl_FragCoord.xy / resolution.xy ) * 20.0 - 10.0;
  //float x = sin(time + length(pos.xy)) + cos((mouse.x / 10) + pos.x);
  //float y = cos(time + length(pos.xy)) + sin((mouse.y / 10)+ pos.y);
  //float z = cos(time + length(pos.xy));
  //frag_colour = vec4( x * 0.5, y * 0.5, z * 0.5, 1.0 );
  frag_colour = vec4(colour, 1.0f);
  //frag_colour = ourColour;
}