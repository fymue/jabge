#ifndef ENGINE_SRC_LAYERSTACK_H_
#define ENGINE_SRC_LAYERSTACK_H_

#include "layer.h"

namespace engine {

class PUB_API LayerStack {
 private:
  using LStack = std::vector<Layer*>;

  LStack _layer_stack;
  LStack::iterator _overlay_start;

 public:
  LayerStack() :
    _layer_stack(10), _overlay_start(_layer_stack.begin()) {}

  ~LayerStack();

  // add layer to layer stack
  void push(Layer *layer);

  // add an overlay to the top of the layer stack
  void push_overlay(Layer *overlay);

  // remove layer from layer stack
  void pop(Layer *layer);

  // remove overlay from layer stack
  void pop_overlay(Layer *layer);

  LStack::iterator begin() {
    return _layer_stack.begin();
  }

  LStack::iterator end() {
    return _layer_stack.end();
  }

  LStack::reverse_iterator rbegin() {
    return _layer_stack.rbegin();
  }

  LStack::reverse_iterator rend() {
    return _layer_stack.rend();
  }
};

}  // namespace engine

#endif  // ENGINE_SRC_LAYERSTACK_H_
