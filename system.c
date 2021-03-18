#include "common.h"
#include "system.h"

void initSystems()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        printf("SDL failed to initialize video.\n");

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
        printf("SDL IMG library failed to initialize.\n");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // Do I need this??? seems to set the # of bits in stencil buffer
}

SDL_Window *setWindow()
{
    SDL_Window *w = SDL_CreateWindow("Alex", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
    if(w == NULL)
        printf("Window failed to create.\n");

    SDL_GLContext context = SDL_GL_CreateContext(w);
    if(context == NULL)
        printf("GL context failed.\n");
    
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress))
        printf("glad failed to load.\n");
    
    glViewport(0, 0, 1024, 768); // Will need a function if window size changes

    return w;
}

void cleanUpSystems()
{
    //SDL_GL_DeleteContext(context);
    SDL_Quit();
}