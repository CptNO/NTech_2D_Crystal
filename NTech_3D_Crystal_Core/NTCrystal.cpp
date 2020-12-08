#include "NTErrors.h"
#include "NTCrystal.h"
#include <SDL.h>
#include <glfw3.h>

namespace NTCrystal {

    int init() {
        //Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);
		if (!glfwInit()){
			fatalError("GLFW init Error!!");
		}
			
        //Tell SDL that we want a double buffered window so we dont get
        //any flickering
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        return 0;
    }

}