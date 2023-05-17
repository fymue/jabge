#ifndef APP_SRC_LAYERS_H_
#define APP_SRC_LAYERS_H_

#include "engine.h"

class TestLayer: public engine::Layer {
 public:
  TestLayer(const engine::WindowData &data) :
    Layer(data) {}

  TestLayer(const char *name, const engine::WindowData &data) :
    Layer(name, data) {}

  ~TestLayer() {}

  void on_event(engine::Event *e) override {
    APP_LOG_INFO(*e);
  }

  void on_update() override {
    APP_LOG_INFO(*this);
  }
};

#endif  // APP_SRC_LAYERS_H_
