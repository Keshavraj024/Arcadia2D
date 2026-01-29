#include "Core/EngineVisitor.h"

#include "Core/Engine.h"

void EngineVisitor::operator()(const sf::Event::Closed&) { engine.EventWindowClose(); }

void EngineVisitor::operator()(const sf::Event::Resized& resizedSize) {
  engine.EventWindowResize(resizedSize.size);
}

void EngineVisitor::operator()(const sf::Event::FocusLost&) { engine.EventWindowFocusLost(); }

void EngineVisitor::operator()(const sf::Event::FocusGained&) { engine.EventWindowFocusGain(); }

void EngineVisitor::operator()(const sf::Event::JoystickConnected& joystick) {
  engine.EventJoystickConnected(joystick.joystickId);
}
void EngineVisitor::operator()(const sf::Event::JoystickDisconnected& joystick) {
  engine.EventJoystickDisconnected(joystick.joystickId);
}
void EngineVisitor::operator()(const sf::Event::MouseButtonPressed&) {
  engine.EventMouseButtonPressed();
}

void EngineVisitor::operator()(const sf::Event::KeyPressed& key) {
    if(key.control && key.shift && key.scancode == sf::Keyboard::Scan::S)
        engine.EventWindowScreenshot();
}
