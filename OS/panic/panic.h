#pragma once

/** Print an error message and stop the CPU forever. Never returns. */
[[noreturn]] void panic(const char* message);