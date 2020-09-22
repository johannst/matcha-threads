/* Copyright (c) 2020 Johannes Stoelp */

#if !defined(linux) || (!defined(__x86_64__) && !defined(__amd64__))
static_assert(false, "Matcha Threads only supported on Linux x86_64!");
#endif
