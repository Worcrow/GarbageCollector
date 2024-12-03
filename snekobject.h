#ifndef __SNEAK_OBJ__
#define __SNEAK_OBJ__
//boot.dev

typedef struct sneak_object snek_object_t;

typedef enum snek_kind {
	INTEGER,
  FLOAT,
  STRING,
  VECTOR3,
  ARRAY,
}	snek_object_kind_t;

typedef union snek_data {
	int   v_int;
  float v_float;
  char  *v_string;
}	snek_object_data_t;

typedef struct snek_array {
  size_t        size;
  snek_object_t **elements;
} snek_array_t;

typedef struct snek_vector {
  snek_object_t *x;
  snek_object_t *y;
  snek_object_t *z;
} snek_vector_t;

typedef struct sneak_object {
	snek_object_kind_t	kind;
	snek_object_data_t	data;
  snek_vector_t       v_vector3;
  snek_array_t        v_array;
  long int            ref_count;
}	snek_object_t;

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z); 
snek_object_t *new_snek_array(size_t size);

#endif
