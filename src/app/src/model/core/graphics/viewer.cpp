
#include "viewer.h"

#include <iostream>
#include <QOpenGLFunctions>
#include <QApplication>
#include "lc_client/eng_graphics/texture.h"
#include <QOpenGLDebugLogger>

Viewer::Viewer() {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setVersion(4, 3);
    setFormat(format);
    QSurfaceFormat::setDefaultFormat(format);

    //setSurfaceType(QWindow::OpenGLSurface);

    this->resize(1280, 720);
}

void Viewer::initializeGL()
{
    std::cout << "init gl" << std::endl;

    this->show();

    initializeOpenGLFunctions();

    QOpenGLContext* pCurrent = context();
    doneCurrent();

    m_pViewerThread = new ViewerThread(this);

    QOpenGLContext *shared = m_pViewerThread->m_context;
    shared->setFormat(pCurrent->format());
    shared->setShareContext(pCurrent);
    shared->create();

    shared->moveToThread(m_pViewerThread);

    QOffscreenSurface *surface = m_pViewerThread->m_surface;
    surface->setFormat(shared->format());
    surface->create();

    std::cout << "QSurface version: " << surface->format().version().first << "." << surface->format().version().second << std::endl;

    glViewport(0, 0, 1280, 720);

    connect(m_pViewerThread, SIGNAL(started()), m_pViewerThread, SLOT(initializeGL()));
    connect(m_pViewerThread, SIGNAL(updateViewer()), this, SLOT(update()));

    m_pViewerThread->moveToThread(m_pViewerThread);

    this->create();
    this->makeCurrent();

    QOpenGLDebugLogger *logger = new QOpenGLDebugLogger(this);
    logger->initialize();

    connect(logger, &QOpenGLDebugLogger::messageLogged, this, &Viewer::debugMessage);
    logger->startLogging();

    const std::string vshSource =
        "#version 430 core\r\n" // note linebreak
        "layout (location = 0) in vec2 aPos;"
        "layout (location = 1) in vec2 aTexCoords;"

        "out vec2 TexCoords;"

        "void main()"
        "{"
        "gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);"
        "TexCoords = aTexCoords;"
        "}";

    const std::string fshSource =
        "#version 430 core\r\n" // note linebreak
        "out vec4 FragColor;"
        "in vec2 TexCoords;"

        "uniform sampler2D screenTexture;"

        "void main()"
        "{"
        "vec4 color = texture(screenTexture, TexCoords);"
        "FragColor = color; /*vec4((0.0 + color.x) / 2, (1.0 + color.y) / 2, (0.0 + color.z) / 2, 1.0);*/"
        "}";

    m_shaderProgram = glCreateProgram();

    //glObjectLabel(GL_PROGRAM, m_shaderProgram, -1, "displayProgram");

    int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fshPtr = fshSource.c_str();
    glShaderSource(fragShader, 1, &fshPtr, 0);
    glCompileShader(fragShader);

    int successF;
    char infoLogF[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &successF);

    if (successF) {
        std::cout << "Fragment shader compiled. " << std::endl;
    }
    else {
        glGetShaderInfoLog(fragShader, 512, 0, infoLogF);
        std::cerr << "Failed to compile fragment shader: \n " << infoLogF << std::endl;
    }
    glAttachShader(m_shaderProgram, fragShader);

    int vertShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertPtr = vshSource.c_str();
    glShaderSource(vertShader, 1, &vertPtr, 0);
    glCompileShader(vertShader);

    int successV;
    char infoLogV[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &successV);

    if (successV) {
        std::cout << "Vertex shader compiled. " << std::endl;
    }
    else {
        glGetShaderInfoLog(vertShader, 512, 0, infoLogV);
        std::cerr << "Failed to compile vertex shader: \n " << infoLogV << std::endl;
    }
    glAttachShader(m_shaderProgram, vertShader);

    glLinkProgram(m_shaderProgram);

    int successPrg;
    char infoLogPrg[512];
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &successPrg);

    if (successPrg) {
        std::cout << "gl_shader_work: shader program linked successfully: " << m_shaderProgram << std::endl;
    }
    else {
        glGetProgramInfoLog(m_shaderProgram, 512, 0, infoLogPrg);
        std::cerr << "gl_shader_work: shader program link failure: \n" << infoLogPrg << std::endl;
    }

    glUniform1i(glGetUniformLocation(m_shaderProgram, "screenTexture"), TextureType::FRAMEBUFFER);

    float quadVertices[] = {// positions // texCoords
                            -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                            -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};

    unsigned int quadVBO;
    glGenVertexArrays(1, &m_framebufferVao);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(m_framebufferVao);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    m_pViewerThread->start();

    Q_ASSERT_X(this->context()->supportsThreadedOpenGL(), "Viewer", "Platform doesn`t support threaded OpenGL.");

    isInited = true;
}

void Viewer::paintGL()
{
    this->makeCurrent();

    glViewport(0, 0, width(), height());

    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE0 + TextureType::FRAMEBUFFER);
    unsigned int texture = m_pViewerThread->getFramebufferTexture();
    glBindTexture(GL_TEXTURE_2D, texture);

    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shaderProgram);

    glBindVertexArray(m_framebufferVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Viewer::resizeGL(int width, int height)
{

}

void Viewer::debugMessage(const QOpenGLDebugMessage &debugMessage)
{
    std::cerr << debugMessage.message().toStdString() << std::endl;
}
