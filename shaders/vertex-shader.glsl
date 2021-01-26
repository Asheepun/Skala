#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 bPos;
out vec2 bTexCoord;

uniform mat4 transformations;

void main(){

	gl_Position = transformations * vec4(aPos.x, aPos.y, aPos.z, 1.0);

	bPos = aPos;

	bTexCoord = aTexCoord;

}
