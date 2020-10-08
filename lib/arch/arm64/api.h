/* Copyright (c) 2020 Johannes Stoelp */

#pragma once

extern "C" void yield(const void* new_stack, void** old_stack);
void* init_stack(void* stack_ptr, void (*entry)(void*), const void* ctx);
