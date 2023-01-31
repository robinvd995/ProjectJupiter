#pragma once

// Enables the engine logger
#define JPT_ENGINE_ENABLE_LOGGER

// Uses GLFW inputs
#define JPT_ENABLE_GLFW_INPUT

// Define if dummy functions want to be set before the graphics API binding to avoid nullptr
#define JPT_RENDER_BINDINGS_USE_DUMMY_BINDS

// Define if openGL is enabled
// #define JPT_ENABLE_OPENGL

// Define if the config parser trims whitespaces from the config files
#define JPT_CONFIG_TRIM_WHITESPACES
