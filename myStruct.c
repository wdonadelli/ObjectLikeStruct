#include <stdio.h>

/* Step 1 */

typedef struct {
	char value;
	void (*set)(char);
	char (*get)(void);
} t_myStruct;

/* Step 2 */

void __myStruct_set__ (t_myStruct *self, char val);
char __myStruct_get__ (t_myStruct *self);

/* Step 3 */

#define __MYSTRUCT_SET__(SELF) \
\
	void __myStruct_set__##SELF (char val) { \
		__myStruct_set__(&SELF, val); \
	} \
	SELF.set = __myStruct_set__##SELF;


#define __MYSTRUCT_GET__(SELF) \
\
	char __myStruct_get__##SELF (void) { \
		return __myStruct_get__(&SELF); \
	} \
	SELF.get = __myStruct_get__##SELF;

/* Step 4 */

#define new_myStruct(OBJECT, VALUE) \
\
	t_myStruct OBJECT; \
	OBJECT.value = VALUE; \
	__MYSTRUCT_SET__(OBJECT); \
	__MYSTRUCT_GET__(OBJECT); \

/* Step 5 */

void __myStruct_set__ (t_myStruct *self, char val) {
	self->value = val;
}

char __myStruct_get__ (t_myStruct *self) {
	return self->value;
}

/* Testing */

void main() {

	printf("----------------------------------\n");
	printf("new_myStruct(x, 'X');\n\nnew_myStruct(y, 'Y');\n\n");
	new_myStruct(x, 'X');
	new_myStruct(y, 'Y');

	printf("----------------------------------\n");
	printf("x.get();\n\t->'%c'\n\ny.get();\n\t->'%c'\n\n", x.get(), y.get());

	printf("----------------------------------\n");
	printf("x.set('r');\n\ny.set('p');\n\n");
	x.set('r');
	y.set('p');

	printf("----------------------------------\n");
	printf("x.get();\n\t->'%c'\n\ny.get();\n\t->'%c'\n\n", x.get(), y.get());
	
}

/*
To compile in GCC and run on linux
	gcc -o myStruct myStruct.c
	./myStruct
*/
