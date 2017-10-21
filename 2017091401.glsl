#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 position = ( gl_FragCoord.xy / resolution.x ) + vec2(0.0, time / 10.0) + mouse / 4.0;
	
	float color = step( cos((position.x + 1.0) * 100.0) * sin(position.y * 100.0), 0.0 );

	gl_FragColor = vec4( vec3( color ), 1.0 );

}
