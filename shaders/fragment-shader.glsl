#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D inputTexture;

uniform vec4 color;

uniform vec2 textureSize;

vec4 TexColor;

void main(){

	TexColor = texture(inputTexture, TexCoord);

	if(TexColor.w == 0){
		discard;
	}

	FragColor = color;

}
