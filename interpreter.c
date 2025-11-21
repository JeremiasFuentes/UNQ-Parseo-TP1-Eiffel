#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "value.h"
#include "ast.h"
#include "symtab.h"

/* Forward */
Value eval_expr(Expr *e, Scope *scope);
void exec_stmts(Stmts *stmts, Scope *scope);
void exec_stmt(Stmt *s, Scope *scope);
Feature *find_feature(ClassNode *klass, const char *name);

void interpret_class(ClassNode *c){
  /* find feature 'make' or 'main' and execute it */
  const char *entry = "make";
  Feature *f = find_feature(c, entry);
  if(!f) f = find_feature(c, "main");
  if(!f){
    fprintf(stderr,"No entry feature 'make' or 'main' found in class %s\n", c->name);
    return;
  }
  /* create global scope for class */
  Scope *global = scope_create(NULL);
  /* create local scope for feature */
  Scope *feat_scope = scope_create(global);
  /* populate locals */
  if(f->locals && f->locals->first){
    LocalDecl *ld = f->locals->first;
    while(ld){
      scope_set(feat_scope, ld->name, make_int_value(0));
      ld = ld->next;
    }
  }
  exec_stmts(f->body, feat_scope);
  scope_free(feat_scope);
  scope_free(global);
}

Feature *find_feature(ClassNode *klass, const char *name){
  Feature *cur = klass->features?klass->features->first:NULL;
  while(cur){
    if(strcmp(cur->name,name)==0) return cur;
    cur = cur->next;
  }
  return NULL;
}

void exec_stmts(Stmts *stmts, Scope *scope){
  if(!stmts) return;
  Stmt *s = stmts->first;
  while(s){
    exec_stmt(s, scope);
    s = s->next;
  }
}

void exec_stmt(Stmt *s, Scope *scope){
  if(!s) return;
  switch(s->kind){
    case STMT_ASSIGN: {
      Value v = eval_expr(s->assign_expr, scope);
      scope_set(scope, s->assign_name, v);
    } break;
    case STMT_PRINT: {
      Value v = eval_expr(s->print_expr, scope);
      runtime_print(v);
      if(v.type==TYPE_STRING) free(v.s);
    } break;
    case STMT_IF: {
      Value c = eval_expr(s->cond, scope);
      int cond = 0;
      if(c.type==TYPE_INT) cond = (c.i!=0);
      else if(c.type==TYPE_REAL) cond = (c.r!=0.0);
      else if(c.type==TYPE_STRING) cond = (c.s && strlen(c.s)>0);
      if(cond) exec_stmts(s->then_branch, scope); else exec_stmts(s->else_branch, scope);
      if(c.type==TYPE_STRING) free(c.s);
    } break;
    case STMT_FROM_UNTIL: {
      /* execute init */
      exec_stmts(s->from_init, scope);
      while(1){
        Value c = eval_expr(s->until_cond, scope);
        int cond = 0;
        if(c.type==TYPE_INT) cond = (c.i!=0);
        else if(c.type==TYPE_REAL) cond = (c.r!=0.0);
        else if(c.type==TYPE_STRING) cond = (c.s && strlen(c.s)>0);
        if(c.type==TYPE_STRING) free(c.s);
        if(cond) break;
        exec_stmts(s->loop_body, scope);
      }
    } break;
    case STMT_CALL: {
      /* call feature in same class; we only support no params and single-level calls */
      Feature *f = find_feature(((Program*)0)->klass, s->assign_name);
      /* it's hard to get class pointer here; instead we do a simpler approach: call by name
         is supported only within same feature scope — so we won't support nested calls here.
         To keep it simple, you can call functions by directly mapping to variables that are features
         in future improvements. For now, print a notice. */
      /* For practical behaviour: try to call a function by name stored in a global table is out of scope */
      fprintf(stderr, "Call to feature '%s' not supported in this simplified interpreter.\n", s->assign_name);
    } break;
    default: break;
  }
}

Value eval_expr(Expr *e, Scope *scope){
  if(!e) return make_void_value();
  switch(e->kind){
    case EXPR_INT: return make_int_value(e->i);
    case EXPR_REAL: return make_real_value(e->r);
    case EXPR_STRING: return make_string_value(e->s);
    case EXPR_VAR: {
      Value v;
      if(scope_get(scope, e->s, &v)) return v;
      else { char buf[256]; snprintf(buf,sizeof(buf),"Variable '%s' no definida", e->s); runtime_error(buf); return make_void_value(); }
    }
    case EXPR_BINOP: {
      Value L = eval_expr(e->left, scope);
      Value R = eval_expr(e->right, scope);
      /* numeric promotion: if any real -> real */
      int isReal = (L.type==TYPE_REAL || R.type==TYPE_REAL);
      if(strcmp(e->s,"+")==0){
        if(isReal) return make_real_value((L.type==TYPE_REAL?L.r:L.i)+(R.type==TYPE_REAL?R.r:R.i));
        else return make_int_value(L.i + R.i);
      } else if(strcmp(e->s,"-")==0){
        if(isReal) return make_real_value((L.type==TYPE_REAL?L.r:L.i)-(R.type==TYPE_REAL?R.r:R.i));
        else return make_int_value(L.i - R.i);
      } else if(strcmp(e->s,"*")==0){
        if(isReal) return make_real_value((L.type==TYPE_REAL?L.r:L.i)*(R.type==TYPE_REAL?R.r:R.i));
        else return make_int_value(L.i * R.i);
      } else if(strcmp(e->s,"/")==0){
        if(isReal) return make_real_value((L.type==TYPE_REAL?L.r:L.i)/(R.type==TYPE_REAL?R.r:R.i));
        else return make_int_value(L.i / R.i);
      } else if(strcmp(e->s,"=")==0){
        if(isReal) return make_int_value(((L.type==TYPE_REAL?L.r:L.i) == (R.type==TYPE_REAL?R.r:R.i))?1:0);
        else return make_int_value(L.i == R.i);
      } else if(strcmp(e->s,"<")==0){
        if(isReal) return make_int_value(((L.type==TYPE_REAL?L.r:L.i) < (R.type==TYPE_REAL?R.r:R.i))?1:0);
        else return make_int_value(L.i < R.i);
      } else if(strcmp(e->s,">")==0){
        if(isReal) return make_int_value(((L.type==TYPE_REAL?L.r:L.i) > (R.type==TYPE_REAL?R.r:R.i))?1:0);
        else return make_int_value(L.i > R.i);
      } else if(strcmp(e->s,"<=")==0){
        if(isReal) return make_int_value(((L.type==TYPE_REAL?L.r:L.i) <= (R.type==TYPE_REAL?R.r:R.i))?1:0);
        else return make_int_value(L.i <= R.i);
      } else if(strcmp(e->s,">=")==0){
        if(isReal) return make_int_value(((L.type==TYPE_REAL?L.r:L.i) >= (R.type==TYPE_REAL?R.r:R.i))?1:0);
        else return make_int_value(L.i >= R.i);
      }
      return make_void_value();
    }
    default: return make_void_value();
  }
}
