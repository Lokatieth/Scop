#version 400

precision mediump float;
flat in vec3 colour;
// in vec3 gl_PrimitiveID;
in vec3 position;
out vec4 frag_colour;

in vec3 texcoord;

uniform sampler2D ourTexture;




precision mediump float;

uniform float time;
uniform float texon;
uniform float perlstr;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float tx,ty;



float map(float value, float min1, float max1, float min2, float max2)
{
	return min2 + (max2 - min2) * ((value - min2) / (max2 - min2));
} 

float timeConst = map(sin(time/3)/2 + 1, 0.5, 1.5, 1, 1.0001);
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(-0.470,-0.540)))
                 * 43758.521);
}

float noise (in vec2 st) {
    vec2 i = ceil(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.000,0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3-2.0*f);
     u = smoothstep(0.0,1.0,f);

    // Mix 4 coorners porcentages
    return (mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y);
}
void main( void ) {
	vec2 st = texcoord.zy;
    vec2 pos = vec2(st*perlstr * timeConst *  5);
    float n = noise(pos);
    //  n = 1;
	

	// frag_colour = vec4(
	// texture(ourTexture, texcoord.zy).rgb* texon
	// + (colour.rgb * (1 - texon)),
	// 0.0f
	//  );
	frag_colour = vec4(
	texture(ourTexture, texcoord.zy * n).rgb * texon
	+ (colour.rgb * (1 - texon)),
	0.0f
	 );

}

// void main() {
//     vec2 st = position.xy;

//     // Scale the coordinate system to see
//     // some noise in action
//     vec2 pos = vec2(st*5.0);

//     // Use the noise function
//     float n = noise(pos);

//     frag_colour = vec4(vec3(n), 1.0);
// }
