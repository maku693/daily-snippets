function createGLSLTag(gl, type) {
  return function(template, ...substitutions) {
    const shader = gl.createShader(type);
    const source = String.raw(template, substitutions);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    return shader;
  };
}

export function createFrag(gl) {
  return createGLSLTag(gl, gl.FRAGMENT_SHADER);
}

export function createVert(gl) {
  return createGLSLTag(gl, gl.VERTEX_SHADER);
}
