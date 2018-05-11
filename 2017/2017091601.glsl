#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 position = gl_FragCoord.xy / resolution.x - 0.5;
	
	float value = sin( ( position.x + time * 0.5 ) * 10.0 ) * 0.1;
	float color = 1.0 - smoothstep( 0.0, 0.003, abs( position.y + value ) );

	gl_FragColor = vec4( vec3( color ), 1.0 );

}
