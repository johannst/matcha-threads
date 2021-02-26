/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

#if !defined(linux)
static_assert(false, "Matcha Threads only supported on Linux!");
#endif

#if defined(__x86_64__) || defined(__amd64__)
#    include "arch/x86_64/api.h"
#elif defined(__aarch64__)
#    include "arch/arm64/api.h"
#elif defined(__arm__)
#    include "arch/arm/api.h"
#else
static_assert(false, "Unsupported architecture!");
#endif
