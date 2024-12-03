#include "snekobject.h"


snek_object_t *new_snek_integer(int value) {
	snek_object_t *new_object;

	new_object = malloc(sizeof(snek_object_t));
	if (!new_object)
		return (NULL);
	new_object->kind = INTEGER;
	new_object->data.v_int = value;
	return (new_object);
}