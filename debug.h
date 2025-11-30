#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>

extern bool debug_print_tokens;
extern bool debug_print_env_actions;

void print_token(const char *name, const char *lexeme);
void print_env_action(const char *action, const char *trigger);

#endif