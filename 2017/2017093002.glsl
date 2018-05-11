#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const int NUM_SAMPLES = 8;

float image(vec2 uv) {
	return distance( uv, vec2( 0 ) ) < 0.1 ? 1.0 : 0.0;
}

void main( void ) {

	vec2 position = ( gl_FragCoord.xy * 2.0 - resolution ) / min( resolution.x, resolution.y );
	vec2 velocity = ( mouse - vec2( 0.5 ) ) * 0.1;

	float color = 0.0;

	for (int i = 1; i < NUM_SAMPLES; i++) {
		vec2 offset = velocity * ( float( i ) / float( NUM_SAMPLES - 1 ) - 0.5 );
		color += image( position + offset );
	}
	color /= float( NUM_SAMPLES );

	gl_FragColor = vec4( vec3( color ), 1.0 );

}
