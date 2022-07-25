#pragma once

#include "Configuration.h"

#include <cstdint>
#include "JupiterCore/Core.h"

typedef uint64_t	l_uint;
typedef uint32_t	uint;
typedef uint16_t	s_uint;
typedef uint8_t		b_uint;

#ifdef JPT_ENGINE_ENABLE_LOGGER
#define JPT_ENGINE_INFO(msg, ...) Jupiter::Engine::n_EngineLogger->info(msg, __VA_ARGS__)
#define JPT_ENGINE_ERROR(msg, ...) Jupiter::Engine::n_EngineLogger->error(msg, __VA_ARGS__)
#define JPT_ENGINE_TRACE(msg, ...) Jupiter::Engine::n_EngineLogger->trace(msg, __VA_ARGS__)
#define JPT_ENGINE_WARN(msg, ...) Jupiter::Engine::n_EngineLogger->warn(msg, __VA_ARGS__)
#else
#define JPT_ENGINE_INFO(msg, ...)
#define JPT_ENGINE_ERROR(msg, ...)
#define JPT_ENGINE_TRACE(msg, ...)
#define JPT_ENGINE_WARN(msg, ...)
#endif // JPT_ENGINE_ENABLE_LOGGER

namespace Jupiter::Engine {

	inline Jupiter::Logger* n_EngineLogger = nullptr;
	void initializeEngineLogger(l_uint flags);
	void deleteLogger();
}

// ----- GLFW Input -----
#ifdef JPT_ENABLE_GLFW_INPUT

#define JPT_MOUSE_BUTTON_COUNT 8
#define JPT_KEYBOARD_BUTTON_COUNT 350
#define JPT_CONTROLLER_BUTTON_COUNT 12

//Source: GLFW/glfw3.h
#define JPT_KEY_SPACE              32
#define JPT_KEY_APOSTROPHE         39  /* ' */
#define JPT_KEY_COMMA              44  /* , */
#define JPT_KEY_MINUS              45  /* - */
#define JPT_KEY_PERIOD             46  /* . */
#define JPT_KEY_SLASH              47  /* / */
#define JPT_KEY_0                  48
#define JPT_KEY_1                  49
#define JPT_KEY_2                  50
#define JPT_KEY_3                  51
#define JPT_KEY_4                  52
#define JPT_KEY_5                  53
#define JPT_KEY_6                  54
#define JPT_KEY_7                  55
#define JPT_KEY_8                  56
#define JPT_KEY_9                  57
#define JPT_KEY_SEMICOLON          59  /* ; */
#define JPT_KEY_EQUAL              61  /* = */
#define JPT_KEY_A                  65
#define JPT_KEY_B                  66
#define JPT_KEY_C                  67
#define JPT_KEY_D                  68
#define JPT_KEY_E                  69
#define JPT_KEY_F                  70
#define JPT_KEY_G                  71
#define JPT_KEY_H                  72
#define JPT_KEY_I                  73
#define JPT_KEY_J                  74
#define JPT_KEY_K                  75
#define JPT_KEY_L                  76
#define JPT_KEY_M                  77
#define JPT_KEY_N                  78
#define JPT_KEY_O                  79
#define JPT_KEY_P                  80
#define JPT_KEY_Q                  81
#define JPT_KEY_R                  82
#define JPT_KEY_S                  83
#define JPT_KEY_T                  84
#define JPT_KEY_U                  85
#define JPT_KEY_V                  86
#define JPT_KEY_W                  87
#define JPT_KEY_X                  88
#define JPT_KEY_Y                  89
#define JPT_KEY_Z                  90
#define JPT_KEY_LEFT_BRACKET       91  /* [ */
#define JPT_KEY_BACKSLASH          92  /* \ */
#define JPT_KEY_RIGHT_BRACKET      93  /* ] */
#define JPT_KEY_GRAVE_ACCENT       96  /* ` */
#define JPT_KEY_WORLD_1            161 /* non-US #1 */
#define JPT_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define JPT_KEY_ESCAPE             256
#define JPT_KEY_ENTER              257
#define JPT_KEY_TAB                258
#define JPT_KEY_BACKSPACE          259
#define JPT_KEY_INSERT             260
#define JPT_KEY_DELETE             261
#define JPT_KEY_RIGHT              262
#define JPT_KEY_LEFT               263
#define JPT_KEY_DOWN               264
#define JPT_KEY_UP                 265
#define JPT_KEY_PAGE_UP            266
#define JPT_KEY_PAGE_DOWN          267
#define JPT_KEY_HOME               268
#define JPT_KEY_END                269
#define JPT_KEY_CAPS_LOCK          280
#define JPT_KEY_SCROLL_LOCK        281
#define JPT_KEY_NUM_LOCK           282
#define JPT_KEY_PRINT_SCREEN       283
#define JPT_KEY_PAUSE              284
#define JPT_KEY_F1                 290
#define JPT_KEY_F2                 291
#define JPT_KEY_F3                 292
#define JPT_KEY_F4                 293
#define JPT_KEY_F5                 294
#define JPT_KEY_F6                 295
#define JPT_KEY_F7                 296
#define JPT_KEY_F8                 297
#define JPT_KEY_F9                 298
#define JPT_KEY_F10                299
#define JPT_KEY_F11                300
#define JPT_KEY_F12                301
#define JPT_KEY_F13                302
#define JPT_KEY_F14                303
#define JPT_KEY_F15                304
#define JPT_KEY_F16                305
#define JPT_KEY_F17                306
#define JPT_KEY_F18                307
#define JPT_KEY_F19                308
#define JPT_KEY_F20                309
#define JPT_KEY_F21                310
#define JPT_KEY_F22                311
#define JPT_KEY_F23                312
#define JPT_KEY_F24                313
#define JPT_KEY_F25                314
#define JPT_KEY_KP_0               320
#define JPT_KEY_KP_1               321
#define JPT_KEY_KP_2               322
#define JPT_KEY_KP_3               323
#define JPT_KEY_KP_4               324
#define JPT_KEY_KP_5               325
#define JPT_KEY_KP_6               326
#define JPT_KEY_KP_7               327
#define JPT_KEY_KP_8               328
#define JPT_KEY_KP_9               329
#define JPT_KEY_KP_DECIMAL         330
#define JPT_KEY_KP_DIVIDE          331
#define JPT_KEY_KP_MULTIPLY        332
#define JPT_KEY_KP_SUBTRACT        333
#define JPT_KEY_KP_ADD             334
#define JPT_KEY_KP_ENTER           335
#define JPT_KEY_KP_EQUAL           336
#define JPT_KEY_LEFT_SHIFT         340
#define JPT_KEY_LEFT_CONTROL       341
#define JPT_KEY_LEFT_ALT           342
#define JPT_KEY_LEFT_SUPER         343
#define JPT_KEY_RIGHT_SHIFT        344
#define JPT_KEY_RIGHT_CONTROL      345
#define JPT_KEY_RIGHT_ALT          346
#define JPT_KEY_RIGHT_SUPER        347
#define JPT_KEY_MENU               348
#endif // JPT_ENABLE_KEY_CODES
