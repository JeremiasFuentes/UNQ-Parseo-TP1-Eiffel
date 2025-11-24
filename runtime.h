#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"

void rt_print(Value v);
void rt_runtime_error(int line, const char *fmt, ...);

#endif
