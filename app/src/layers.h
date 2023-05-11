#ifndef APP_SRC_LAYERS_H_
#define APP_SRC_LAYERS_H_

#include "engine.h"

class TestLayer: public engine::Layer {
 public:
  TestLayer() :
    Layer() {}

  ~TestLayer() {}

  void on_event(engine::Event *e) override {
    APP_LOG_INFO(*e);
  }

  void on_update() override {
    APP_LOG_INFO("Updating TestLayer");
  }
};

#endif  // APP_SRC_LAYERS_H_
