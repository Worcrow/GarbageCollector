#ifndef __SNEAK_OBJ__
#define __SNEAK_OBJ__

typedef enum snek_kind {
	INTEGER,
}	snek_object_kind_t;

typedef union snek_data {
	int v_int;
}	snek_object_data_t;

typedef struct sneak_object {
	snek_object_kind_t	kind;
	snek_object_data_t	data;
}	snek_object_t;

#endif
