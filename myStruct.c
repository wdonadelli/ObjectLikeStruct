#include <stdio.h>
/* Construir um objeto contendo um atributo e duas funções (set/get) */

/* 1) Definir a estrutura do objeto */

typedef struct {
	char value;
	void (*set)(char);
	char (*get)(void);
} t_myStruct;

/* 2) Definir protótipos dos métodos */

void __myStruct_set__ (t_myStruct *self, char val);
char __myStruct_get__ (t_myStruct *self);

/* 3) Definir a macro de criação dos métodos (protótipo, definição e função) */

#define __MYSTRUCT_SET__(SELF) \
\
	void __myStruct_set__##SELF (char val) { \
		__myStruct_set__(&SELF, val); \
	} \
	SELF.set = __myStruct_set__##SELF;

/*------------------------------------------------------*/
	
#define __MYSTRUCT_GET__(SELF) \
\
	char __myStruct_get__##SELF (void) { \
		return __myStruct_get__(&SELF); \
	} \
	SELF.get = __myStruct_get__##SELF;

/* 4) Definir a função construtora */

#define new_myStruct(OBJECT, VALUE) \
\
	t_myStruct OBJECT; \
	OBJECT.value = VALUE; \
	__MYSTRUCT_SET__(OBJECT); \
	__MYSTRUCT_GET__(OBJECT); \

void __myStruct_set__ (t_myStruct *self, char val) {
	self->value = val;
}

char __myStruct_get__ (t_myStruct *self) {
	return self->value;
}

void main() {

	/* testando */
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
new_uigtk(x);
x.load("file.ui");
x.handler(F_UIGTK(gtk_main_quit));
x.builder();
x.window();
x.main()
*/
