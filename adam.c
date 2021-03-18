#include "common.h"
#include "shaders.h"
#include "system.h"

float verts[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

int checkEvents(SDL_Event event)
{
    if(event.type == SDL_QUIT)
            return 0;
        else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_w:
                    printf("W\n");
                break;
                case SDLK_s:
                break;
                case SDLK_a:
                break;
                case SDLK_d:
                break;
            }
        }
    return 1;
}

int main(int argc, char *args[])
{
    initSystems();
    SDL_Window *window = setWindow();

    unsigned int shaderProgram = setupShaderPrgm();
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // Copy vertices into buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    // Set buffer attributes or how the data is organized
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int quit = 1;
    SDL_Event event;
    SDL_GL_SwapWindow(window);
    
    while(quit)
    {
        // Input
        SDL_PollEvent(&event);
        quit = checkEvents(event);

        // Logic / Physics
        
        // Draw
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);
    }

    cleanUpSystems();
    return 0;
}