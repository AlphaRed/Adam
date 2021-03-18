#include "common.h"
#include "shaders.h"

void readShaderFile(char *filename, const char **shader)
{
    char *buffer;
    long length;
    int num;

    FILE *file = fopen(filename, "rb");
    if(file == NULL)
    {
        printf("Error reading file.\n");
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length + 1);
    if(buffer == NULL)
    {
        printf("Error allocating memory for buffer.\n");
    }

    num = fread(buffer, 1, length, file);
    if(num == 0)
    {
        printf("Nothing was read from shader file.\n");
    }

    fclose(file);
    buffer[length] = '\0';
    *shader = buffer;
}

unsigned int setupShader(char *filename, int type)
{
    unsigned int shader;
    int success;
    char infoLog[512];

    if(type == 0) // Vertex shader
    {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    else if(type == 1) // Fragment shader
    {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    const char *shaderSrc;
    readShaderFile(filename, &shaderSrc);
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glad_glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error compiling shader\n");
    }
    return shader;
}

unsigned int setupShaderPrgm()
{
    int success;
    char infoLog[512];
    unsigned int shaderProgram = glCreateProgram();

    unsigned int vShader = setupShader("shaders/vertex.shader", 0);
    unsigned int fShader = setupShader("shaders/fragment.shader", 1);
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Error: Shader program linking failed.\n");
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return shaderProgram;
}