#include "enginepch.h"
#include "layerstack.h"

namespace engine {

LayerStack::LayerStack() {
  _layer_stack.reserve(10);
  _overlay_start = _layer_stack.begin();
}

LayerStack::~LayerStack() {
  for (Layer *layer : _layer_stack) {
    delete layer;
  }
}

void LayerStack::push(Layer *layer) {
  // always insert new layer BEFORE _overlay_start position so
  // overlay layers always sit above the other layers of the layer stack
  _overlay_start = _layer_stack.emplace(_overlay_start, layer);
}

void LayerStack::pop(Layer *layer) {
  auto match = std::find(_layer_stack.begin(), _layer_stack.end(), layer);
  if (match != _layer_stack.end()) {
    // if the input layer was found in the layer stack,
    // delete it and decrement the overlay start
    // (since one of the normal layers has just been removed)
    _layer_stack.erase(match);
    _overlay_start--;
  }
}

void LayerStack::push_overlay(Layer *layer) {
  _layer_stack.push_back(layer);
}

void LayerStack::pop_overlay(Layer *layer) {
  auto match = std::find(_layer_stack.begin(), _layer_stack.end(), layer);
  if (match != _layer_stack.end()) {
    _layer_stack.erase(match);
  }
}

}  // namespace engine
