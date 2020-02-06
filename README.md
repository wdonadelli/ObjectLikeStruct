# Object-like structure for C language

The present method describes how to use the data type `struct` of the C language to work in a similar way to objects.

This method has been tested with the `gcc` compiler version (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0.

To exemplify the creation of such structures, an object will be built containing an attribute, which will contain `char` type information, and two methods, one to define the argument and the other to obtain it. When building this structure, it will be allowed to enter an initial value for the attribute.

## Step 1: define the structure

The structure will be called `t_myStruct` and will have the following organization:

1. The `value` attribute will be used to store the character that will be defined in the construction of the structure and by the `set` method;
2. The `set` method will store a pointer to a function that will set the value of the `value` argument; and
3. The `get` method will store a pointer to a function that will get the value from the `value` argument;.

The structure will look like this:

```c
typedef struct {
	char value;
	void (*set)(char);
	char (*get)(void);
} t_myStruct;
```

## Step 2: define function prototypes

For each method specified, a function prototype must be created.

The function linked to the method must contain the argument `self` that will indicate a pointer to the address of the structure. When it is necessary to access the structure data, it will be through this argument that the action will be performed.

### Defining the prototype for the `set` method

The prototype of the `set` method will be called `__myStruct_set__` and will not return any values.

As `set` will define the value of the `value` attribute of the structure, in addition to the `self` argument, the prototype must also contain an argument that will be passed to the method to promote the change of the attribute.

Therefore, the function prototype can be as follows: 

```c
void __myStruct_set__ (t_myStruct *self, char val);
```

### Defining the prototype for the `get` method

The prototype of the `get` method will be called `__myStruct_get__` and will return information of type `char`.

Since `set` will return the value of the `value` attribute, only the `self` argument is required.

Therefore, the function prototype can be as follows: 

```c
char __myStruct_get__ (t_myStruct *self);
```

## Step 3: define the method constructor

When calling the constructor of the structure, each method will receive the address of a specific function, made just for him, pointing to the structure itself.

The purpose of this function is to define the `self` argument and call the prototype of its respective function. The function prototype, created in step 2, is the one who will actually carry out the action.

The method builder will only have the necessary arguments for the performance of the action, the `self` argument should be left out, as the method builder will define and pass this argument on to the function prototype.

The type of data that the method will return must be the same as the prototype and the name defined in the structure.

As each method will have a specific function, the function names cannot be repeated, or it will cause an error in addressing the structure.

### Defining the `set` method builder

The macro to define the constructor of the `set` method will look like this:

```c
#define __MYSTRUCT_SET__(SELF) \
\
	void __myStruct_set__##SELF (char val) { \
		__myStruct_set__(&SELF, val); \
	} \
	SELF.set = __myStruct_set__##SELF;
```

### Defining the `get` method builder

The macro to define the constructor of the `get` method will look like this:

```c
#define __MYSTRUCT_GET__(SELF) \
\
	char __myStruct_get__##SELF (void) { \
		return __myStruct_get__(&SELF); \
	} \
	SELF.get = __myStruct_get__##SELF;
```

## Step 4: defining the structure builder

The name of the constructor will be `new_myStruct` and will take as an argument the variable that will be assigned to the structure and other arguments that will define the initial values, if any. In the example discussed here, you will receive the initial value of the `value` attribute.

The construction macro will link the variable to the structure type, define the initial values ​​of the attributes and link the methods to the addresses of their respective builders.

The macro will have the following organization:

```c
#define new_myStruct(OBJECT, VALUE) \
\
	t_myStruct OBJECT; \
	OBJECT.value = VALUE; \
	__MYSTRUCT_SET__(OBJECT); \
	__MYSTRUCT_GET__(OBJECT); \
```

When calling the constructor in the form of `new_myStruct(var, 'x')`, the following actions will be performed by the macros:

```c
/* new_myStruct(var, 'x') */

/* Defines the data type of the variable */
t_myStruct var;

/* Assigns the 'x' character to the "value" attribute */
var.value = 'x';

/* Build a specific function for the "set" method */
void __myStruct_set__var (char val) {
	__myStruct_set__(&var, val);
}

/* Assign the specific function to the "set" method */
var.set = __myStruct_set__var;

/* Build a specific function for the "get" method */
char __myStruct_get__var () {
	return __myStruct_get__(&var);
}

/* Assign the specific function to the "get" method */
var.get = __myStruct_get__var;
```

## Step 5: defining prototype actions

The prototypes, when accessing the structure by the `self` argument, will be obtaining the address for the structure, so you must use the correct way to access it, that is, using the `->` format.

### Defining the "__myStruct_set__" function

```c
void __myStruct_set__ (t_myStruct *self, char val)
{
	self->value = val;
}
```

### Defining the "__myStruct_get__" function

```c
char __myStruct_get__ (t_myStruct *self)
{
	return self->value;
}
```

## Testing

Testing

When compiling and executing the commands below, ...

```c
void main()
{

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
```

...the following result should be displayed on the screen:

```
----------------------------------
new_myStruct(x, 'X');

new_myStruct(y, 'Y');

----------------------------------
x.get();
	->'X'

y.get();
	->'Y'

----------------------------------
x.set('r');

y.set('p');

----------------------------------
x.get();
	->'r'

y.get();
	->'p'
```

## Author

- Willian Donadelli (<wdonadelli@gmail.com>)
