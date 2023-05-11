#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

/*
 * Public API of the engine, which exposes every core part
 * of the engine and includes the entry point of the engine/
 * the program that uses the engine;
 * this file should be included in any program that wants
 * to use the engine
*/

#include "src/core.h"
#include "src/log.h"
#include "src/application.h"
#include "src/entrypoint.h"
#include "src/window.h"
#include "src/types.h"
#include "layerstack.h"
#include "src/event/event.h"

#endif  // ENGINE_ENGINE_H_