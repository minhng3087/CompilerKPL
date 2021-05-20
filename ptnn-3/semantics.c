/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */
#include "debug.h"
#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  Scope* currentScope = symtab->currentScope;
  Object* object = NULL;
  while(currentScope != NULL) {
    object = findObject(currentScope->objList, name);
    if(object != NULL)
      return object;
    currentScope = currentScope->outer;
  }
  return findObject(symtab->globalObjectList, name);
}

void checkFreshIdent(char *name) {
  if(lookupObject(name) != NULL) {
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
  }
}

Object* checkDeclaredIdent(char* name) {
  Object* ident = lookupObject(name);
  if(ident == NULL) {
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  }
  
  return ident;
  
}

Object* checkDeclaredConstant(char* name) {
  Object* cont = checkDeclaredIdent(name);
  if(cont->kind != OBJ_CONSTANT) {
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  }
  return cont;
}

Object* checkDeclaredType(char* name) {
  Object* type = checkDeclaredIdent(name);
  if(type->kind != OBJ_TYPE) {
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  }
  return type;
}

Object* checkDeclaredVariable(char* name) {
  Object* var = checkDeclaredIdent(name);
  if(var->kind != OBJ_VARIABLE) {
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
  }
  return var;
}

Object* checkDeclaredFunction(char* name) {
  Object* function = checkDeclaredIdent(name);
  if(function->kind != OBJ_FUNCTION) {
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  }
  return function;
}

Object* checkDeclaredProcedure(char* name) {
  Object* procedure = checkDeclaredIdent(name);
  if(procedure->kind != OBJ_PROCEDURE) {
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  }
  return procedure;
}

Object* checkDeclaredLValueIdent(char* name) {
  Object *object = checkDeclaredIdent(name);
  if( object->kind != OBJ_FUNCTION && object->kind != OBJ_VARIABLE && object->kind != OBJ_PARAMETER) {
    error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo); 
  }

  return object;
}