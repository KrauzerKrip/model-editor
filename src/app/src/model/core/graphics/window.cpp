#include "window.h"
#include <iostream>

Window::Window(Viewer* pViewer, int width, int height, std::array<int, 2> aspectRatio, bool vSync, float fov) {
    m_pViewer = pViewer;

    m_width = width;
    m_height = height;
}

void Window::init() {
}

void Window::startFrame()
{

}

std::array<int, 2> Window::getSize() {
    std::array<int, 2> size;
    size[0] = m_width;
    size[1] = m_height;

    return size;
}

void Window::update() {
    //QMetaObject::invokeMethod(m_pViewer, "update");
    //m_pViewer->update();
};

bool Window::windowShouldClose() {
    return false;
};
void Window::terminate() {};
IInput* Window::getInput() {return nullptr;};
void Window::setMode(WindowMode mode) {m_windowMode = mode;};
WindowMode Window::getMode() {return m_windowMode;};
void Window::setResizeCallback(std::function<void(int, int)> callback) {};
std::array<int, 2> Window::getAspectRatio() {return m_pAspectRatio;};
float Window::getFov() {
    return m_fov;
};
void Window::setFov(float fov) {
    m_fov = fov;
};
