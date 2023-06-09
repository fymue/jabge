#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

/*
 * Public API of the engine, which exposes every core part
 * of the engine and includes the entry point of the engine/
 * the program that uses the engine;
 * this file should be included in any program that wants
 * to use the engine
*/

#include "core.h"
#include "log.h"
#include "application.h"
#include "entrypoint.h"
#include "window.h"
#include "types.h"
#include "layer.h"
#include "layer/imguilayer.h"
#include "layerstack.h"
#include "event/event.h"

#endif  // ENGINE_ENGINE_H_
