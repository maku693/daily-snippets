#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float eps = 0.01;

void main( void ) {

	vec2 position = ( ( gl_FragCoord.xy / resolution.xy ) - vec2( 1.0, 0.5 ) ) * 4.0;
	
	float value = cos( position.x * 7.0 + time * 3.0 ) * sin( position.x * time * 0.2 ) * cos( position.x + sin( time ) );
	
	vec3 color = distance( position.y, value ) < 0.01 ? vec3( 0.0, 1.0, 0.0 ) : vec3( 0.0 );

	gl_FragColor = vec4( color, 1.0 );

}
