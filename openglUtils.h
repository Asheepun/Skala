#ifndef OPENGL_UTILS_H_
#define OPENGL_UTILS_H_

typedef struct OpenglUtils_ShaderProgram{
	unsigned int ID;
	char * name;
}OpenglUtils_ShaderProgram;

typedef struct OpenglUtils_Texture{
	unsigned int ID;
	char *name;
}OpenglUtils_Texture;

unsigned int getCompiledShader(char *, GLenum);

#endif
