#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "utils.h"
#include "openglUtils.h"

char *readFile_mustFree(char *filePath){

	char *buffer = malloc(sizeof(char) * 1024);
	FILE *fd = NULL;
	long fileLength = 0;

	fd = fopen(filePath, "r");

	char c;
	while((c = fgetc(fd)) != EOF){
		buffer[fileLength] = c;
		fileLength++;
	}

	for(int i = fileLength; i < 1024; i++){
		buffer[i] = NULL;
	}
	
	fclose(fd);

	return buffer;

}

unsigned int getCompiledShader(char *shaderSourcePath, GLenum type){
	char *shaderSource = readFile_mustFree(shaderSourcePath);

	unsigned int shader;
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("FAILED TO COMPILE SHADER: %s\n%s\n", shaderSourcePath, infoLog);
	}

	free(shaderSource);

	return shader;
}

void OpenglUtils_Renderer_init(OpenglUtils_Renderer *renderer_p, float width, float height){

	renderer_p->offset = getVec2f(0, 0);
	renderer_p->width = width;
	renderer_p->height = height;

	float rectangleVertices[] = {
		1, 1, 0, 		1, 0,
		-1, 1, 0, 		0, 0,
		-1, -1, 0, 		0, 1,

		1, 1, 0, 		1, 0,
		1, -1, 0, 		1, 1,
		-1, -1, 0, 		0, 1,
	};

	glGenBuffers(1, &renderer_p->VBO);

	glGenVertexArrays(1, &renderer_p->VAO);

	glBindVertexArray(renderer_p->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, renderer_p->VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenTextures(1, &renderer_p->textTextureID);

}

unsigned int OpenglUtils_Renderer_drawTexture(OpenglUtils_Renderer renderer, Vec2f pos, Vec2f size, Vec4f color, unsigned int facing, Vec2f borderSize, unsigned int textureID, unsigned int shaderProgramID){

	Mat4f transformations = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	Mat4f_translate(&transformations, -1, 1, 0);

	Mat4f_translate(&transformations, size.x / renderer.width, -size.y / renderer.height, 0);

	Mat4f_translate(&transformations, 2 * pos.x / renderer.width, 2 * -pos.y / renderer.height, 0);

	Mat4f_translate(&transformations, 2 * renderer.offset.x / renderer.width, 2 * -renderer.offset.y / renderer.height, 0);

	Mat4f_scale(&transformations, size.x / renderer.width, size.y / renderer.height, 1);

	glUseProgram(shaderProgramID);

	unsigned int transformationsLocation = glGetUniformLocation(shaderProgramID, "transformations");
	glUniformMatrix4fv(transformationsLocation, 1, GL_TRUE, transformations.values);

	unsigned int colorLocation = glGetUniformLocation(shaderProgramID, "color");
	glUniform4fv(colorLocation, 1, &color);

	unsigned int facingLocation = glGetUniformLocation(shaderProgramID, "facing");
	glUniform1iv(facingLocation, 1, &facing);

	float adjustedBorderSizeX = borderSize.x * size.y / size.x / size.y;
	float adjustedBorderSizeY = borderSize.y / size.y;

	unsigned int borderSizeXLocation = glGetUniformLocation(shaderProgramID, "borderSizeX");
	glUniform1fv(borderSizeXLocation, 1, &adjustedBorderSizeX);

	unsigned int borderSizeYLocation = glGetUniformLocation(shaderProgramID, "borderSizeY");
	glUniform1fv(borderSizeYLocation, 1, &adjustedBorderSizeY);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindVertexArray(renderer.VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

Mat4f OpenglUtils_Renderer_getBodyTransformations(OpenglUtils_Renderer renderer, Vec2f pos, Vec2f size){

	Mat4f transformations = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	Mat4f_translate(&transformations, -1, 1, 0);

	Mat4f_translate(&transformations, size.x / renderer.width, -size.y / renderer.height, 0);

	Mat4f_translate(&transformations, 2 * pos.x / renderer.width, 2 * -pos.y / renderer.height, 0);

	Mat4f_translate(&transformations, 2 * renderer.offset.x / renderer.width, 2 * -renderer.offset.y / renderer.height, 0);

	Mat4f_scale(&transformations, size.x / renderer.width, size.y / renderer.height, 1);

	return transformations;

}
