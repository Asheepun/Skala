#version 100

precision highp float;

uniform float alpha;

uniform vec3 color;

void main(){

	gl_FragColor = vec4(color.x, color.y, color.z, alpha);

}
