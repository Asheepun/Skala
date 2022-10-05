#version 100

precision highp float;

attribute vec2 vertexPosition;
attribute vec2 textureVertex;

varying vec2 textureCoord;

uniform float posX;
uniform float posY;

uniform float rendererWidth;
uniform float rendererHeight;

uniform float spriteWidth;
uniform float spriteHeight;

void main(){

	float width = spriteWidth / rendererWidth;
	float height = spriteHeight / rendererHeight;

	gl_Position = vec4(
		posX + width + -1.0 + vertexPosition.x * width,
		-posY + -height + 1.0 + vertexPosition.y * height,
		0.0,
		1.0
	);

	textureCoord = textureVertex;

}
