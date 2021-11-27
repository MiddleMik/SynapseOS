/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#pragma once


#include <kernel.h>


int strlen(const char *str);
void *memcpy(void *destination, const void *source, size_t n);
void *memset(void *destination, int c, size_t n);