#ifndef VALUE_H
#define VALUE_H

typedef enum {
    TYPE_INT,
    TYPE_REAL,
    TYPE_STRING,
//    TYPE_BOOL,
    TYPE_VOID
} ValueType;

typedef struct {
    ValueType type;
    int i;
    double r;
    char *s;
//    bool b;
} Value;

// Constructores
Value make_int_value(int x);
Value make_real_value(double x);
Value make_string_value(const char *s);
//Value make_bool_value(bool x);
Value make_void_value(void);

#endif
