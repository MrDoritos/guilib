#include "shader_program.h"

GLuint shader_program_t::lastProgramId = -1;

bool shader_program_t::load() {
    for (auto *shader : shaders) {
        if (!shader->isLoaded())
            shader->load();

        assert(shader->isLoaded() && "Shader not loaded\n");
    }

    programId = glCreateProgram();
    
    for (auto *shader : shaders)
        glAttachShader(programId, shader->shaderId);

    glLinkProgram(programId);

    int success = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        char infoLog[513];
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cout << "Error: Linking shader\n" << infoLog << std::endl;
        return glfail;
    }

    return glsuccess && get_uniform_locations();
}