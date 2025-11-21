#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "symtab.h"

/* constructors */

Program *make_program(ClassNode *c){
  Program *p = malloc(sizeof(Program));
  p->klass = c;
  return p;
}

ClassNode *make_class(char *name, Features *f){
  ClassNode *c = malloc(sizeof(ClassNode));
  c->name = strdup(name);
  c->features = f;
  return c;
}

/* features */
Feature *make_feature(char *name, Locals *locals, Stmts *body){
  Feature *f = calloc(1,sizeof(Feature));
  f->name = strdup(name);
  f->locals = locals;
  f->body = body;
  f->next = NULL;
  return f;
}

Features *single_feature(Feature *f){
  Features *fs = malloc(sizeof(Features));
  fs->first = f;
  return fs;
}
Features *append_feature(Features *list, Feature *f){
  if(!list) return single_feature(f);
  Feature *cur = list->first;
  while(cur->next) cur = cur->next;
  cur->next = f;
  return list;
}

/* locals */
LocalDecl *make_local(char *name){
  LocalDecl *d = malloc(sizeof(LocalDecl));
  d->name = strdup(name);
  d->next = NULL;
  return d;
}
LocalDecl *append_local(LocalDecl *list, char *name){
  LocalDecl *n = make_local(name);
  if(!list) return n;
  LocalDecl *cur = list;
  while(cur->next) cur = cur->next;
  cur->next = n;
  return list;
}
Locals *single_locals(LocalDecl *d){
  Locals *l = malloc(sizeof(Locals));
  l->first = d;
  return l;
}

/* statements */
Stmts *append_stmt(Stmts *list, Stmt *s){
  if(!list){ list = malloc(sizeof(Stmts)); list->first = s; return list; }
  Stmt *cur = list->first;
  while(cur->next) cur = cur->next;
  cur->next = s;
  return list;
}

Stmt *make_assign(char *name, Expr *e){
  Stmt *s = calloc(1,sizeof(Stmt));
  s->kind = STMT_ASSIGN;
  s->assign_name = strdup(name);
  s->assign_expr = e;
  s->next = NULL;
  return s;
}

Stmt *make_print(Expr *e){
  Stmt *s = calloc(1,sizeof(Stmt));
  s->kind = STMT_PRINT;
  s->print_expr = e;
  return s;
}

Stmt *make_if(Expr *cond, Stmts *t, Stmts *e){
  Stmt *s = calloc(1,sizeof(Stmt));
  s->kind = STMT_IF;
  s->cond = cond;
  s->then_branch = t;
  s->else_branch = e;
  return s;
}

Stmt *make_from_until(Stmts *init, Expr *untilc, Stmts *body){
  Stmt *s = calloc(1,sizeof(Stmt));
  s->kind = STMT_FROM_UNTIL;
  s->from_init = init;
  s->until_cond = untilc;
  s->loop_body = body;
  return s;
}

Stmt *make_call(char *name){
  Stmt *s = calloc(1,sizeof(Stmt));
  s->kind = STMT_CALL;
  s->assign_name = strdup(name);
  return s;
}

/* expressions */
Expr *make_int_literal(long v){
  Expr *e = calloc(1,sizeof(Expr)); e->kind = EXPR_INT; e->i = v; return e;
}
Expr *make_real_literal(double v){
  Expr *e = calloc(1,sizeof(Expr)); e->kind = EXPR_REAL; e->r = v; return e;
}
Expr *make_string_literal(char *s){
  Expr *e = calloc(1,sizeof(Expr)); e->kind = EXPR_STRING; e->s = strdup(s); return e;
}
Expr *make_varref(char *name){
  Expr *e = calloc(1,sizeof(Expr)); e->kind = EXPR_VAR; e->s = strdup(name); return e;
}
Expr *make_binop(const char *op, Expr *l, Expr *r){
  Expr *e = calloc(1,sizeof(Expr)); e->kind = EXPR_BINOP; e->s = strdup(op); e->left = l; e->right = r; return e;
}

/* interpreter entry */
extern void interpret_class(ClassNode *c);
void interpret_program(Program *p){
  if(!p) return;
  interpret_class(p->klass);
}

/* free helpers (simple, not freeing all recursively for brevity) */
void free_program(Program *p){
  if(!p) return;
  /* freeing shallow to avoid long code; in real project free everything */
  free(p->klass->name);
  free(p->klass);
  free(p);
}
