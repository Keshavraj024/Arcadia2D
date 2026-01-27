#include "Core/EngineVisitor.h"

#include "Core/Engine.h"

void EngineVisitor::operator()(const sf::Event::Closed &)
{
  engine.EngineWindowClose();
}

void EngineVisitor::operator()(const sf::Event::Resized& resizedSize) {
  engine.EngineWindowResize(resizedSize.size);
}


void EngineVisitor::operator()(const sf::Event::FocusLost&) {
  engine.EngineWindowFocusLost();
}

void EngineVisitor::operator()(const sf::Event::FocusGained&) {
  engine.EngineWindowFocusGain();
}

