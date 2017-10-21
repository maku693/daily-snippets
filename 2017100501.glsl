#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 position = ( gl_FragCoord.xy / resolution.xy - 0.5 ) * 2.0;

	float color = 1.0 - ( sin( time * 2.0 ) * 0.5 + 0.5) * distance( vec2( 0.0 ), position );

	gl_FragColor = vec4( vec3( color ), 1.0 );

}
