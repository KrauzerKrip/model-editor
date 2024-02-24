#include "render.h"
#include "qassert.h"

#include <iostream>
#include <QOpenGLDebugLogger>

Render::Render(int width, int height, float fov)
{
    m_width = width;
    m_height = height;
    m_fov = fov;
}

void Render::init()
{
    initializeOpenGLFunctions();

    QOpenGLDebugLogger *logger = new QOpenGLDebugLogger();
    assert(logger->initialize());

    m_pDebugger = new OpenGLDebugger(logger);
    logger->startLogging();

    glViewport(0, 0, m_width, m_height);
    glClearColor(117.0f / 255, 187.0f / 255, 253.0f / 255, 1.0f);

//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CCW);

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glObjectLabel(GL_FRAMEBUFFER, m_fbo, -1, "renderFramebuffer");

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    Q_ASSERT_X((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Render", "Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char *vertexShaderSource = "#version 430 core\r\n"
                                     "layout (location = 0) in vec3 aPos;"
                                     "void main()"
                                     "{"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
                                     "}";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentShaderSource = "#version 430 core\r\n"
                                       "out vec4 FragColor;"
                                       "void main()"
                                       "{"
                                       "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
                                       "}";


    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();

    //glObjectLabel(GL_PROGRAM, shaderProgram, -1, "triangleProgram");

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &VAO);

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Render::render()
{

    m_i++;

        // ..:: Drawing code (in render loop) :: ..
        // 4. draw the object

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    //glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //m_texture = m_renderFbo->texture();

    //std::swap(m_renderFbo, m_displayFbo);
}

void Render::clear()
{

}

void Render::cleanUp()
{

}

int Render::getFramebufferTexture()
{
    return (int) m_texture;
}
