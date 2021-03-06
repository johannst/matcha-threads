/* Copyright (c) 2021 Johannes Stoelp */

#pragma once

// Platform specific API.
// When integrating a new platform the following functions must be implemented.

// Called once for every `Thread` object to setup the initial state of the
// threads stack.
//
// Arguments:
//   stack_ptr    Pointer to the bottom of the stack.
//   entry        Function pointer to the entry-point called on first `yield`.
//   ctx          Context passed to `entry`.
//
// Return:
//   Return pointer to the top of the stack after initialization.
//
// Requirements:
//   - Stack must be descending.
//   - Returned stack pointer must be aligned according to the platform specification.
//   - Stack must be setup in a way that a consequent call to `yield` will call
//     `entry` with `ctx` supplied as argument.
void* init_stack(void* stack_ptr, void (*entry)(void*), const void* ctx);

// Switch execution context from current stack to `new_stack`.
//
// Arguments:
//   new_stack    Stack pointer of new context to switch to.
//   old_stack    Pointer to location to store the current stack pointer.
extern "C" void yield(const void* new_stack, void** old_stack);
