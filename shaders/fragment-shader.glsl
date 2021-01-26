#version 330 core
out vec4 FragColor;

in vec3 bPos;
in vec2 bTexCoord;

uniform sampler2D inputTexture;

uniform vec4 color;

uniform int facing = 1;

uniform float borderSizeX = 0;
uniform float borderSizeY = 0;

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
		FragColor = vec4(0.0, 0.0, 0.0, 1);
	}

	if(bPos.x < -1 + borderSizeX
	|| bPos.x > 1 - borderSizeX
	|| bPos.y < -1 + borderSizeY
	|| bPos.y > 1 - borderSizeY){
		FragColor = vec4(0.13, 0.12, 0.11, 1);
	}

}
