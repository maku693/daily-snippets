#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

vec2 pixel = gl_FragCoord.xy / resolution;

float checker(vec2 uv) {
	return cos( uv.x * 100.0 ) * sin( uv.y * 100.0 ) < 0.0 ? 1.0 : 0.0;
}

void main( void ) {

	vec2 position = ( gl_FragCoord.xy / resolution.x );
	vec2 velocity = mouse - gl_FragCoord.xy;

	float color = 0.0;

	int numSamples = 4;

	for (int i = 1; i < numSamples; i++) {
		vec2 offset = velocity * ( float( i ) / float( nSamples - 1 ) - 0.5 );
		color += checker( position + offset );
	}

	gl_FragColor = vec4( vec3( color ), 1.0 );

}
