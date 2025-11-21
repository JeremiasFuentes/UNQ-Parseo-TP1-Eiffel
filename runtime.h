#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"

void runtime_print(Value v);
void runtime_error(const char *msg);

#endif /* RUNTIME_H */
