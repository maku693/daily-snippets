#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 position = (gl_FragCoord.xy / resolution.y) - vec2( 1.0, 0.5 );

	float color = 0.0;
	color += abs( position.x ) < 0.1 ? 0.5 : 0.0;
	color += abs( position.y ) < 0.1 ? 0.5 : 0.0;

	gl_FragColor = vec4( vec3( color ), 1.0 );

}
