#version 330 core
out vec4 FragColor;

in vec2 bTexCoord;

uniform sampler2D inputTexture;

uniform vec4 color;

uniform int facing = 1;

vec4 TexColor;
vec2 TexCoord;

void main(){

	TexCoord = bTexCoord;

	if(facing == 0){
		TexCoord.x = 1 - TexCoord.x;
	}

	TexColor = texture(inputTexture, TexCoord);

	if(TexColor.w == 0){
		discard;
	}

	FragColor = color;

	if(TexColor.x == 0
	&& TexColor.y == 0
	&& TexColor.z == 0){
		FragColor = vec4(0, 0, 0, 0);
	}

}
