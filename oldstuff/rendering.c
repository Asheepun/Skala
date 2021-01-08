//#include "miniglut/miniglut.h"
#include "math.h"
#include "stdio.h"
#include "pthread.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include "rendering.h"
#include "unistd.h"
#include "signal.h"

#define __WINDOW_LAYER_GL__

unsigned int getPixelIndexFromTexture(Texture texture, int x, int y){
	return (texture.width * y + x) * 4;
}

Vec4f getColorFromTexture(Texture texture, int x, int y){
	return getVec4f(
		(float)(texture.data[(texture.width * y + x) * 4 + 0] / 255),
		(float)(texture.data[(texture.width * y + x) * 4 + 1] / 255),
		(float)(texture.data[(texture.width * y + x) * 4 + 2] / 255),
		(float)(texture.data[(texture.width * y + x) * 4 + 3] / 255)
	);
}

Pixel getPixelFromColor(Vec4f color){
	Pixel pixel = { color.z * 255, color.y * 255, color.x * 255 };

	return pixel;
}

void Texture_init(Texture *texture_p){

	if(texture_p->inited){
		printf("***\n");
		printf("TEXTURE IS INITED TWICE, MUST FIRST DE INIT!\n");
		printf("***\n");
	}

	texture_p->data = NULL;
	texture_p->width = 0;
	texture_p->height = 0;
	texture_p->inited = true;
}

void TextureSliceMap_init(TextureSliceMap *textureSliceMap_p, Texture texture){

	textureSliceMap_p->sliceArrays = malloc(texture.height * sizeof(Array));

	for(int y = 0; y < texture.height; y++){

		Array_init(&textureSliceMap_p->sliceArrays[y], sizeof(TextureSlice));

		TextureSlice *currentSlice_p;
		bool transparent = true;

		for(int x = 0; x < texture.width; x++){

			unsigned int pixelIndex = getPixelIndexFromTexture(texture, x, y);

			if(texture.data[pixelIndex + 3] != 0){

				if(transparent == true){
					currentSlice_p = Array_addItem(&textureSliceMap_p->sliceArrays[y]);
					currentSlice_p->x = x;
					currentSlice_p->width = 0;
				}

				currentSlice_p->width++;


				transparent = false;
			}
			if(texture.data[pixelIndex + 3] == 0){

				transparent = true;

			}
		
		}
	
	}

	int slices = 0;
	for(int i = 0; i < texture.height; i++){
		slices += textureSliceMap_p->sliceArrays[i].length;
	}

}

void Texture_loadData(Texture *texture_p, char *imagePath){

	/*
	int *comp;

	texture_p->data = stbi_load(imagePath, &texture_p->width, &texture_p->height, &comp, 4);

	if(texture_p->data == NULL){
		printf("Failed to load texture %s\n", imagePath);
	}
	*/

}

void Texture_freeData(Texture *texture_p){
	
	free(texture_p->data);

	texture_p->data = NULL;
	
}

void Renderer_init(Renderer *renderer_p){

	renderer_p->pixels = NULL;
	renderer_p->width = 0;
	renderer_p->height = 0;

	renderer_p->scale = getVec2f(1, 1);

	Array_init(&renderer_p->textures, sizeof(Texture));

}

void Renderer_setSize(Renderer *renderer_p, float width, float height){

	renderer_p->width = width;
	renderer_p->height = height;

	if(renderer_p->pixels != NULL){
		free(renderer_p->pixels);
	}

	renderer_p->pixels = malloc(renderer_p->width * renderer_p->height * sizeof(Pixel));

}

int Renderer_getPixelIndex(Renderer *renderer_p, int x, int y){

	/*
	if(x < 0
	|| y < 0
	|| x >= renderer_p->width
	|| y >= renderer_p->height){
		return -1;
	}
	*/

#ifdef __WINDOW_LAYER_GL__
	return (renderer_p->height - 1 - y) * renderer_p->width + x;
#else
	return y * renderer_p->width + x;
#endif

}

void Renderer_fillRect(Renderer *renderer_p, int posX, int posY, int width, int height, Vec4f color){

	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){

			int pixelIndex = Renderer_getPixelIndex(renderer_p, posX + x, posY + y);

			renderer_p->pixels[pixelIndex].r = (int)(color.x * 255);
			renderer_p->pixels[pixelIndex].g = (int)(color.y * 255);
			renderer_p->pixels[pixelIndex].b = (int)(color.z * 255);

		}
	}

}

void Renderer_drawTextureSliceMapInSingleColor(Renderer *renderer_p, float inputPosX, float inputPosY, float inputWidth, float inputHeight, TextureSliceMap textureSliceMap, float alpha, Vec4f color ){

	if(inputWidth < 1
	|| inputHeight < 1){
		return;
	}

	float posX = (int)((floor(inputPosX) + renderer_p->offset.x) * renderer_p->scale.x);
	float posY = (int)((floor(inputPosY) + renderer_p->offset.y) * renderer_p->scale.y);

	float width = (int)(floor(inputWidth) * renderer_p->scale.x);
	float height = (int)(floor(inputHeight) * renderer_p->scale.y);

	float screenPosX = posX;
	float screenPosY = posY;
	float screenWidth = width;
	float screenHeight = height;

	if(screenPosX + screenWidth < 0
	|| screenPosX > renderer_p->width
	|| screenPosY + screenHeight < 0
	|| screenPosY > renderer_p->height){
		return;
	}

	if(screenPosX + screenWidth > renderer_p->width){
		screenWidth = renderer_p->width - screenPosX;
	}

	if(screenPosX < 0){
		screenWidth += screenPosX;
		screenPosX = 0;
	}

	if(screenPosY + screenHeight > renderer_p->height){
		screenHeight = renderer_p->height - screenPosY;
	}

	if(screenPosY < 0){
		screenHeight += screenPosY;
		screenPosY = 0;
	}

	if(!renderer_p->multiThreadingOn){

		for(int y = 0; y < screenHeight; y++){

			Array textureSliceArray = textureSliceMap.sliceArrays[(int)(y / screenHeight)];

			for(int i = 0; i < textureSliceArray.length; i++){

				TextureSlice *textureSlice_p = Array_getItemPointerByIndex(&textureSliceArray, i);

				for(int x = 0; x < textureSlice_p->width; x++){

					int pixelIndex = Renderer_getPixelIndex(renderer_p, screenPosX, screenPosY + y);

					Pixel *pixel_p = &renderer_p->pixels[pixelIndex];

					pixel_p->r = pixel_p->r + (color.x * 255 - pixel_p->r) * alpha /** textureAlpha*/ * renderer_p->fadeOutAlpha;
				
				}
				
			}
		
		}


		/*
		for(int y = 0; y < screenHeight; y++){

			int pixelIndex = Renderer_getPixelIndex(renderer_p, screenPosX, screenPosY + y);

			for(int x = 0; x < screenWidth; x++){

				int texturePosX = (int)((x + (screenPosX - posX)) * texture.width / width);
				int texturePosY = (int)((y + (screenPosY - posY)) * texture.height / height);

				int texturePixelIndex = getPixelIndexFromTexture(texture, texturePosX, texturePosY);
			
				float textureAlpha = texture.data[texturePixelIndex + 3] / 255;
				Pixel *pixel_p = &renderer_p->pixels[pixelIndex + x];

				pixel_p->r = pixel_p->r + (color.x * 255 - pixel_p->r) * alpha * textureAlpha * renderer_p->fadeOutAlpha;
				pixel_p->g = pixel_p->g + (color.y * 255 - pixel_p->g) * alpha * textureAlpha * renderer_p->fadeOutAlpha;
				pixel_p->b = pixel_p->b + (color.z * 255 - pixel_p->b) * alpha * textureAlpha * renderer_p->fadeOutAlpha;

			}
		}
		*/
	
	}

}

typedef struct DrawingProcessArguments{
	Renderer *renderer_p;
	float posX;
	float posY;
	float width;
	float height;
	float screenPosX;
	float screenPosY;
	float screenWidth;
	float screenHeight;
	int startY;
	Texture texture;
	float alpha;
	Vec4f color;
}DrawingProcessArguments;

#define NUMBER_OF_DRAWING_THREADS 10
//const int NUMBER_OF_DRAWING_THREADS = 10;

static pthread_t drawingThreads[NUMBER_OF_DRAWING_THREADS];
static DrawingProcessArguments drawingThreadsArguments[NUMBER_OF_DRAWING_THREADS];
//static bool drawingThreadsLocks[NUMBER_OF_DRAWING_THREADS];
static int completedDrawingProcesses = 0;

static pthread_cond_t drawingThreadsConds[NUMBER_OF_DRAWING_THREADS];
static pthread_mutex_t drawingThreadsMutexLocks[NUMBER_OF_DRAWING_THREADS];

static pthread_mutex_t completedDrawingProcessesMutexLock;

static pthread_t drawingProcessTrackingThread;
static pthread_cond_t drawingThreadsAreDoneCond;
static pthread_mutex_t drawingThreadsAreDoneMutex;

size_t callNumber = 0;

void drawingProcess(void *i){

	int index = *(int *)i;

	DrawingProcessArguments *a = &drawingThreadsArguments[index];

	bool drew = false;

	while(1){


		//printf("THREAD IS LISTENING %i\n", index);

		if(drew){
			//completedDrawingProcesses++;
			//printf("completed process: %i\n", completedDrawingProcesses);
			drew = false;
		}

		//pthread_mutex_lock(&drawingThreadsMutexLocks[index]);

		int request = pthread_cond_wait(&drawingThreadsConds[index], &drawingThreadsMutexLocks[index]);
		//printf("REQUEST %i\n", request);

		if(request == 0){

			for(int y = a->startY; y < a->startY + a->screenHeight; y++){
				for(int x = 0; x < a->screenWidth; x++){

					int texturePosX = (int)((x + (a->screenPosX - a->posX)) * a->texture.width / a->width);
					int texturePosY = (int)((y + (a->screenPosY - a->posY)) * a->texture.height / a->height);

					int texturePixelIndex = getPixelIndexFromTexture(a->texture, texturePosX, texturePosY);
					int pixelIndex = Renderer_getPixelIndex(a->renderer_p, a->screenPosX + x, a->screenPosY + y);

					float textureAlpha = a->texture.data[texturePixelIndex + 3] / 255;
					Pixel *pixel_p = &a->renderer_p->pixels[pixelIndex];

					pixel_p->r = pixel_p->r + (a->color.x * 255 - pixel_p->r) * a->alpha * textureAlpha;
					pixel_p->g = pixel_p->g + (a->color.y * 255 - pixel_p->g) * a->alpha * textureAlpha;
					pixel_p->b = pixel_p->b + (a->color.z * 255 - pixel_p->b) * a->alpha * textureAlpha;
				
				}
			}

			drew = true;

			pthread_mutex_lock(&completedDrawingProcessesMutexLock);

			completedDrawingProcesses++;

			pthread_mutex_unlock(&completedDrawingProcessesMutexLock);

			//printf("DREW! %i, %i\n", index, callNumber);

			//printf("COMPLETED PROCESSES: %i\n", completedDrawingProcesses);
			callNumber++;

			//drawingThreadsLocks[index] = false;
		
		}

		//pthread_mutex_unlock(&drawingThreadsMutexLocks[index]);

		//printf("LOOPED!\n");

		//pause();
		
	}

}

void trackingProcess(void *nothing){
	/*
	while(1){
		if(completedDrawingProcesses < NUMBER_OF_DRAWING_THREADS){

			pthread_cond_signal(&drawingThreadsAreDoneCond);

			//printf("COMPLETED ALL PROCESSES\n");

		}
	}
	*/
}

void initDrawingThreads(){
	for(int i = 0; i < NUMBER_OF_DRAWING_THREADS; i++){

		pthread_mutex_init(&drawingThreadsMutexLocks[i], NULL);
		pthread_cond_init(&drawingThreadsConds[i], NULL);

		int *index = malloc(sizeof(int));//gets freed at end of program
		*index = i;

		pthread_create(
			&drawingThreads[i],
			NULL,
			drawingProcess,
			(void *)index
		);

		//drawingThreadsLocks[i] = false;
	
	}

	pthread_mutex_init(&completedDrawingProcessesMutexLock, NULL);

	/*
	pthread_mutex_init(&drawingThreadsAreDoneMutex, NULL);
	pthread_cond_init(&drawingThreadsAreDoneCond, NULL);

	pthread_create(
		&drawingProcessTrackingThread,
		NULL,
		trackingProcess,
		NULL
	);
	*/

}

/*
void Renderer_drawTextureInSingleColor_parallelDrawingProcess(void *arguments){

	//ParallelDrawingProcessArguments *a = (ParallelDrawingProcessArguments *)arguments;

	for(int y = a->startY; y < a->startY + a->screenHeight; y++){
		for(int x = 0; x < a->screenWidth; x++){

			int texturePosX = (int)((x + (a->screenPosX - a->posX)) * a->texture.width / a->width);
			int texturePosY = (int)((y + (a->screenPosY - a->posY)) * a->texture.height / a->height);

			int texturePixelIndex = getPixelIndexFromTexture(a->texture, texturePosX, texturePosY);
			int pixelIndex = Renderer_getPixelIndex(a->renderer_p, a->screenPosX + x, a->screenPosY + y);

			float textureAlpha = a->texture.data[texturePixelIndex + 3] / 255;
			Pixel *pixel_p = &a->renderer_p->pixels[pixelIndex];

			//a->renderer_p->pixels[pixelIndex].r = (int)((1 - (1 - a->color.x * a->alpha * textureAlpha) * (1 - a->renderer_p->pixels[pixelIndex].r / 255)) * 255);
			//a->renderer_p->pixels[pixelIndex].g = (int)((1 - (1 - a->color.y * a->alpha * textureAlpha) * (1 - a->renderer_p->pixels[pixelIndex].g / 255)) * 255);
			//a->renderer_p->pixels[pixelIndex].b = (int)((1 - (1 - a->color.z * a->alpha * textureAlpha) * (1 - a->renderer_p->pixels[pixelIndex].b / 255)) * 255);

			pixel_p->r = pixel_p->r + (a->color.x * 255 - pixel_p->r) * a->alpha * textureAlpha;
			pixel_p->g = pixel_p->g + (a->color.y * 255 - pixel_p->g) * a->alpha * textureAlpha;
			pixel_p->b = pixel_p->b + (a->color.z * 255 - pixel_p->b) * a->alpha * textureAlpha;
		
		}
	}

	//free(arguments);

}
*/

void Renderer_drawTextureInSingleColor(Renderer *renderer_p, float inputPosX, float inputPosY, float inputWidth, float inputHeight, Texture texture, float alpha, Vec4f color){

	if(inputWidth < 1
	|| inputHeight < 1){
		return;
	}

	float posX = (int)((floor(inputPosX) + renderer_p->offset.x) * renderer_p->scale.x);
	float posY = (int)((floor(inputPosY) + renderer_p->offset.y) * renderer_p->scale.y);

	float width = (int)(floor(inputWidth) * renderer_p->scale.x);
	float height = (int)(floor(inputHeight) * renderer_p->scale.y);

	float screenPosX = posX;
	float screenPosY = posY;
	float screenWidth = width;
	float screenHeight = height;

	if(screenPosX + screenWidth < 0
	|| screenPosX > renderer_p->width
	|| screenPosY + screenHeight < 0
	|| screenPosY > renderer_p->height){
		return;
	}

	if(screenPosX + screenWidth > renderer_p->width){
		screenWidth = renderer_p->width - screenPosX;
	}

	if(screenPosX < 0){
		screenWidth += screenPosX;
		screenPosX = 0;
	}

	if(screenPosY + screenHeight > renderer_p->height){
		screenHeight = renderer_p->height - screenPosY;
	}

	if(screenPosY < 0){
		screenHeight += screenPosY;
		screenPosY = 0;
	}

	DrawingProcessArguments baseArguments = {
		renderer_p,
		posX,
		posY,
		width,
		height,
		screenPosX,
		screenPosY,
		screenWidth,
		screenHeight,
		0,
		texture,
		alpha,
		color
	};

	if(!renderer_p->multiThreadingOn){

		for(int y = 0; y < screenHeight; y++){

			int pixelIndex = Renderer_getPixelIndex(renderer_p, screenPosX, screenPosY + y);

			for(int x = 0; x < screenWidth; x++){

				Pixel *pixel_p = &renderer_p->pixels[pixelIndex + x];

				pixel_p->r = pixel_p->r + (color.x * 255 - pixel_p->r);
				pixel_p->g = pixel_p->g + (color.y * 255 - pixel_p->g);
				pixel_p->b = pixel_p->b + (color.z * 255 - pixel_p->b);

				//int texturePosX = (int)((x + (screenPosX - posX)) * texture.width / width);
				//int texturePosY = (int)((y + (screenPosY - posY)) * texture.height / height);

				//int texturePixelIndex = getPixelIndexFromTexture(texture, texturePosX, texturePosY);
			
				/*
				float textureAlpha = texture.data[texturePixelIndex + 3] / 255;
				Pixel *pixel_p = &renderer_p->pixels[pixelIndex + x];

				pixel_p->r = pixel_p->r + (color.x * 255 - pixel_p->r) * alpha * textureAlpha * renderer_p->fadeOutAlpha;
				pixel_p->g = pixel_p->g + (color.y * 255 - pixel_p->g) * alpha * textureAlpha * renderer_p->fadeOutAlpha;
				pixel_p->b = pixel_p->b + (color.z * 255 - pixel_p->b) * alpha * textureAlpha * renderer_p->fadeOutAlpha;
				*/

			}
		}
	
	}else{

		completedDrawingProcesses = 0;

		for(int i = 0; i < NUMBER_OF_DRAWING_THREADS; i++){
			//pthread_mutex_lock(&drawingThreadsMutexLocks[i]);
		}

		for(int i = 0; i < NUMBER_OF_DRAWING_THREADS; i++){

			drawingThreadsArguments[i] = baseArguments;

			drawingThreadsArguments[i].screenHeight /= NUMBER_OF_DRAWING_THREADS;

			drawingThreadsArguments[i].startY = i * screenHeight / NUMBER_OF_DRAWING_THREADS;

			pthread_mutex_lock(&drawingThreadsMutexLocks[i]);

			int rc = pthread_cond_signal(&drawingThreadsConds[i]);

			//printf("SIGNALED! %i, %i\n", i, rc);

			//while(pthread_cond_signal(&drawingThreadsConds[i])){
				//printf("RE TRIED!\n");
			//}

			pthread_mutex_unlock(&drawingThreadsMutexLocks[i]);

			//usleep(1 * NUMBER_OF_DRAWING_THREADS);
		
		}

		for(int i = 0; i < NUMBER_OF_DRAWING_THREADS; i++){
			//pthread_mutex_unlock(&drawingThreadsMutexLocks[i]);
		}

		/*
		pthread_mutex_lock(&drawingThreadsAreDoneMutex);

		pthread_cond_wait(&drawingThreadsAreDoneCond, &drawingThreadsAreDoneMutex);

		printf("%i\n", completedDrawingProcesses);

		pthread_mutex_unlock(&drawingThreadsAreDoneMutex);
		*/
		
		//printf("SIGNAL IS SENT\n");

		//printf("%i\n", rc);

		while(completedDrawingProcesses < NUMBER_OF_DRAWING_THREADS){
			//printf("CHECKING IF PROCESSES ARE DONE!, %i of %i\n", completedDrawingProcesses, NUMBER_OF_DRAWING_THREADS);
		}

	}


	//usleep(1);

	//printf("ALL PROCESSES COMPLETED!\n");

	//usleep(1000);

	//printf("ALL PROCESSES ARE COMPLETED\n");

	/*
	if(screenWidth * screenHeight < renderer_p->singleThreadDrawSizeLimit){

		Renderer_drawTextureInSingleColor_parallelDrawingProcess((void *)&baseArguments);

	}else{

		int numberOfThreads = (int)(screenWidth * screenHeight / renderer_p->singleThreadDrawSizeLimit);

		baseArguments.screenHeight /= numberOfThreads;

		pthread_t threadIDs[numberOfThreads];
		ParallelDrawingProcessArguments arguments[numberOfThreads];

		for(int i = 0; i < numberOfThreads; i++){

			arguments[i] = baseArguments;
			arguments[i].startY = i * screenHeight / numberOfThreads;

			pthread_create(
				&threadIDs[i],
				NULL,
				Renderer_drawTextureInSingleColor_parallelDrawingProcess,
				(void *)&arguments[i]
			);
			
		}

		for(int i = 0; i < numberOfThreads; i++){

			pthread_join(threadIDs[i], NULL);
		
		}
	
	}
	*/

	/*
	for(int y = 0; y < screenHeight; y++){
		for(int x = 0; x < screenWidth; x++){

			int texturePosX = (int)((x + (screenPosX - posX)) * texture.width / width);
			int texturePosY = (int)((y + (screenPosY - posY)) * texture.height / height);

			int texturePixelIndex = getPixelIndexFromTexture(texture, texturePosX, texturePosY);
			int pixelIndex = Renderer_getPixelIndex(renderer_p, screenPosX + x, screenPosY + y);

			float textureAlpha = texture.data[texturePixelIndex + 3] / 255;
			Pixel *pixel_p = &renderer_p->pixels[pixelIndex];

			pixel_p->r = pixel_p->r + (color.x * 255 - pixel_p->r) * alpha * textureAlpha;
			pixel_p->g = pixel_p->g + (color.y * 255 - pixel_p->g) * alpha * textureAlpha;
			pixel_p->b = pixel_p->b + (color.z * 255 - pixel_p->b) * alpha * textureAlpha;
			//pixel_p->r = pixel_p->r - (int)(alpha * textureAlpha * (1 - color.x) * 255);
			//pixel_p->g = pixel_p->g - (int)(alpha * textureAlpha * (1 - color.y) * 255);
			//pixel_p->b = pixel_p->b - (int)(alpha * textureAlpha * (1 - color.z) * 255);

			//pixel_p->r = (int)((1 - (1 - color.x * alpha * textureAlpha) * (1 - pixel_p->r / 255)) * 255);
			//pixel_p->g = (int)((1 - (1 - color.y * alpha * textureAlpha) * (1 - pixel_p->g / 255)) * 255);
			//pixel_p->b = (int)((1 - (1 - color.z * alpha * textureAlpha) * (1 - pixel_p->b / 255)) * 255);
		
		}
	}
	*/

}

void Renderer_testSingleThreadDrawSizeLimit(Renderer *renderer_p){

	float pixelAmount = 1000000;

	float testTimesResult = 0;

	for(int i = 0; i < 10; i++){

		float testStartTime;
		float testEndTime;

		Texture testTexture;
		testTexture.data = malloc(1000 * sizeof(unsigned char));

		//testStartTime = glutGet(GLUT_ELAPSED_TIME);

		//speed test
		for(int i = 0; i < pixelAmount; i++){

			int x = testTexture.data[0];

			int pixelIndex = (int)((float)i * renderer_p->width * renderer_p->height / pixelAmount);

			renderer_p->pixels[pixelIndex].r = 0;
			renderer_p->pixels[pixelIndex].g = 0;
			renderer_p->pixels[pixelIndex].b = 0;

		}

		free(testTexture.data);

		//testEndTime = glutGet(GLUT_ELAPSED_TIME);

		testTimesResult += testEndTime - testStartTime;
		
	}

	testTimesResult /= 10;

	int pixelLimit = (int)(pixelAmount / testTimesResult / 4);

	renderer_p->singleThreadDrawSizeLimit = pixelLimit;

}
