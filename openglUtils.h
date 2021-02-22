#ifndef OPENGL_UTILS_H_
#define OPENGL_UTILS_H_

typedef struct OpenglUtils_Renderer{

	Vec2f offset;
	float width;
	float height;

	unsigned int VAO;
	unsigned int VBO;

	unsigned int textTextureID;

}OpenglUtils_Renderer;

typedef struct OpenglUtils_ShaderProgram{
	unsigned int ID;
	char * name;
}OpenglUtils_ShaderProgram;

typedef struct OpenglUtils_Texture{
	unsigned int ID;
	char *name;
}OpenglUtils_Texture;

unsigned int getCompiledShader(char *, GLenum);

void OpenglUtils_Renderer_init(OpenglUtils_Renderer *, float, float);

unsigned int OpenglUtils_Renderer_drawTexture(OpenglUtils_Renderer, Vec2f, Vec2f, Vec4f, unsigned int, Vec2f, unsigned int, unsigned int);

Mat4f OpenglUtils_Renderer_getBodyTransformations(OpenglUtils_Renderer, Vec2f, Vec2f);

#endif
