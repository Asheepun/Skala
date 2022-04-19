#version 100

precision highp float;

attribute vec2 vertexPosition;

uniform float posX;
uniform float posY;

uniform float spriteWidth;
uniform float spriteHeight;

void main(){

	gl_Position = vec4(
		posX + spriteWidth + -1.0 + vertexPosition.x * spriteWidth,
		-posY + -spriteHeight + 1.0 + vertexPosition.y * spriteHeight,
		0.0,
		1.0
	);

}
