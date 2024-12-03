#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "snekobject.h"


snek_object_t *_new_snek_object() {
  snek_object_t *new_object;

  new_object = calloc(1, sizeof(snek_object_t));
  if (!new_object)
    return (NULL);
  new_object->ref_count = 1;
  return (new_object);
}

void refcount_inc(snek_object_t *obj) {
  if (!obj)
    return (NULL);
  obj->ref_count++;
}

void refcount_free(snek_object_t *obj) {
  int i;

  i = 0;
  if (obj->kind == INTEGER || obj->kind == FLOAT)
    free(obj);
  else if (obj->kind == STRING)
  {
    free(obj->data.v_string);
    free(obj);
  }
  else if (obj->kind == VECTOR3)
  {
    refcount_dec(obj->v_vector3.x);
    refcount_dec(obj->v_vector3.y);
    refcount_dec(obj->v_vector3.z);
  }
  else if (obj->kind == ARRAY)
  {
    while (i < obj->v_array.size)
    {
      refcount_dec(obj->v_array.elements[i]);
      i++;
    }
    free(obj->v_array.elements);
  }
}

void refcount_dec(snek_object_t *obj) {
  if (!obj)
    return (NULL);
  obj->ref_count--;
  if (obj->ref_count == 0)
    refcount_free(obj);
}


snek_object_t *new_snek_vector3(snek_object_t *x,
                                snek_object_t *y,
                                snek_object_t *z) {
  snek_object_t *new_object;

  if (!x || !y || !z)
    return (NULL);
  new_object = malloc(sizeof(snek_object_t));
  if (!new_object)
    return (NULL);
  new_object->kind = VECTOR3;
  new_object->v_vector3.x = x;
  new_object->v_vector3.y = y;
  new_object->v_vector3.z = z;
  refcount_inc(x);
  refcount_inc(y);
  refcount_inc(z);
  return (new_object);
}

int snek_length(snek_object_t *obj) {
 if (!obj)
    return (-1);
  else if (obj->kind == INTEGER || obj->kind == FLOAT)
    return (1);
  else if (obj->kind == STRING)
    return (strlen(obj->data.v_string));
  else if (obj->kind == VECTOR3)
    return (3);
  else if (obj->kind == ARRAY)
    return (obj->v_array.size);
  else
    return (-1);
}

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
  if (!snek_obj || !value || snek_obj->kind != ARRAY || index >= snek_obj->v_array.size)
    return (false);
  value->ref_count++;
  snek_obj->v_array.elements[index]->ref_count--;
  snek_obj->v_array.elements[index] = value;
  return (true);
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
  if (!snek_obj || snek_obj->kind != ARRAY || index >= snek_obj->v_array.size)
    return (NULL);
  return (snek_obj->v_array.elements[index]);
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *new_object;
  snek_object_t **elements;

  new_object = malloc(sizeof(snek_object_t));
  if (!new_object)
    return (NULL);
  elements = calloc(size, sizeof(snek_object_t *));
  if (!elements)
  {
    free(new_object);
    return (NULL);
  }
  new_object->kind = ARRAY;
  new_object->v_array.size = size;
  new_object->v_array.elements = elements;
  return (new_object);
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *new_object;
  size_t        len;
  char          *ret;

  new_object = malloc(sizeof(snek_object_t));
  if (!new_object)
    return (NULL);
  len = strlen(value);
  ret = malloc(sizeof(char) * (len + 1));
  if (!ret)
  {
    free(new_object);
    return (NULL);
  }
  strcpy(ret, value);
  new_object->kind = STRING;
  new_object->data.v_string = ret;
  return (new_object);
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *new_object;

  new_object = malloc(sizeof(snek_object_t));
  if (!new_object)
    return (NULL);
  new_object->kind = FLOAT;
  new_object->data.v_float = value;
  return (new_object);
}

snek_object_t *new_snek_integer(int value) {
	snek_object_t *new_object;

	new_object = malloc(sizeof(snek_object_t));
	if (!new_object)
		return (NULL);
	new_object->kind = INTEGER;
	new_object->data.v_int = value;
	return (new_object);
}

