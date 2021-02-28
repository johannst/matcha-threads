/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

#if !defined(linux)
static_assert(false, "Matcha Threads only supported on Linux!");
#endif

#if defined(__x86_64__) || defined(__amd64__)
// fall-through: x86_64 support
#elif defined(__aarch64__)
// fall-through: arm64 support
#elif defined(__arm__)
// fall-through: armv7 support
#else
static_assert(false, "Unsupported architecture!");
#endif

#include "arch/api.h"
