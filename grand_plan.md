# Grand plan

## Functions
- Named arguments
- Passing parameters
- Closures (and tmp values)
- Function call semantics

	i.e. to avoid passing big objects around (where 'big objects' means 'does not fit into `int`')

		BigType f(int i) {
			if i == 0 {
				return BigType(0);
			} 

			if i == 1 {
				return BigType(1);
			}
			
			return BigType();
		}

		BigType b = f(1, 2, 3);

	translates to

		// TODO `procedure` needed to give a form to intermediate code that is
		// still valid Z? Or are void-returning functions equivalent to
		// procedures? That might mess with overloading.
		procedure f(BigType* result, int i) {
			if i == 0 {
				*result = BigType(0);
				return;
			}
			if i == 1 {
				*result = BigType(1);
				return;
			}

			*result = BigType();
			return;
		}
		BigType b;

## Structs and methods

### Getters and setters

#### For local and global variables

- `foo` translates to `get_foo()`, if one exists.
- `foo = bar` translates to `set_foo(bar)`, if one exists.

#### Normal getters and setters 

- `x.foo` translates to `x.get_foo()`, if one exists.
- `x.foo = bar` translates to `x.set_foo(bar)`, if one exists.

A special case must exist for the getters themselves (and possibly others that
have access to the instance variables):

	type Person {
		int age;
		get_age() {
			// Here, age refers to this.age, not to get_age(), avoiding the infinite
			// loop
			return age;
		}
	}

The convention of prefixing instance (or otherwise private) variables with `_`
might work well with this rule.  We wouldn't need any special cases, since
nobody with their sane mind would do a method called `get__foo`.  Unless they
really needed one &mdash; and then it would possible.

#### Getters and setters with arguments

- `foo(a) = bar` translates to `set_foo(a, bar)`, if one exists.
- `x.foo(a) = bar` translates to `x.set_foo(a, bar)`, if one exists.

In this case, the getter translation is not necessary.

#### Getters and setters without a name

Or: making array-like objects.

- `foo[n]` translates to `foo.get(n)`, if one exists.
- `foo[n] = bar` translates to `foo.set(n, bar)`, if one exists.

#### This reminds me of a `with`-macro that also works with getters and setters:

	with (Error.captureStackTrace = myStackTrace) {
		// do something that calls Error.captureStackTrace()
	}

translates to 

	var orig = Error.captureStackTrace;
	Error.captureStackTrace = myStackTrace;
	// do something that calls Error.captureStackTrace()
	Error.captureStackTrace = orig;

## Basic types / literals
- The usual int8-int64, float32, float64, char set
- Strings (by default, utf8-encoded, char is 32bit)
	- String literals should probably be written with 'single quotes' (since a '
		is faster to type than a ".)
	- no char literals at all, or possibly one-character string literals would
		be char literals that would be coerced to strings if necessary. One
		thing where this might cause problems might be places where switching the
		type changes the function to be called. Otherwise, a character should
		behave in the same way than a one-character string.

		for c in 'x'
			print(c); // c is a char
		for c in 'xyz'
			print(c); // c is a char

		'x'.length // 1
		'xyz'.length // 3
		'x'.bytes // [ 0x78 ]
		'xyz'.bytes // [ 0x78, 0x79, 0x7a ]

- Arrays (both fixed size and resizable; syntax for these)
- Array literals ([1,2,3] instead of {1,2,3})
	- can assign variable size arrays and constant size arrays alike
- Pointers: new syntax
- Compatibility between types important
	- for example, converting fixed size arrays to variable size arrays and vice
		versa (actually, not that easy - need a read-only array / array reference
		type)
- starting from arithmetic types
- custom type casts
## Iteration
- Iterating over data structures (for x in array)
- Consider "ranges" http://www.slideshare.net/rawwell/iteratorsmustgo
## An interlude: ranges
- by which I mean [0...99] or [0...100] 
- A data structure that looks like an array (or whatever)
- May be infinite...
## Looping
- for (int i = 0; i < 10; i++)
- loop { ... }
- while (cond) { ... }
- until (cond) { ... } <==> while (!cond) { ... }
- do { ... } while/until (cond)
- an actually genuine addition:
	do { ... } while/until (cond) { ... }

	For instance:

	do {
		char c = getchar();
	} while (c != EOF) {
		print(c);
	}

	which is the same as usual C version:
	
	char c;
	while ((c = getchar()) != EOF) {
		print(c);
	}

	but cleaner (hopefully); and translates to:

	while (true) {
		char c = getchar();
		if (c == EOF)
			break;
		print(c);
	}

	Actually, using a do-until, that might be rewritten as:

	do {
		var c = getchar();
	} until (c == EOF) {
		print(c);
	}
## Other revamping of C statements
## Reference types, operators
- can temporary values passed to operators be handled without const?
- like with closures
## Templates (min(x, y) { return x < y ? x : y; })
## Modules; C interoperability?
## Error handling, automatic object destruction
- Consider tuples like in go:

	var result, err = server.fetch_names_starting_with('foo')
	if err {
		// Do stuff
	}

	This might give rise to error handling that looks like exception handling.
	Or then not. Automatically generated code at every call side (if cannot be
	proven to be error-safe) may be expensive. I guess that's what burdens C++ as well.

## A possible interesting side adventure

A node.js-like event loop based callback-driven system where synchronous and asynchronous calls would look the same and could be used interchangeably.

- For instance,

f(filename) {
	contents = read_file(filename)
}

// Where read_file would be something like

async read_file(String filename, fn(result, err) cb);

// And therefore would be used exactly like a synchronous read

String read_file_sync(String filename);

// Except that the rest of the function would be wrapped inside the callback
// automatically.

## Macros (compile-time code evaluation with access to code as data)
## Const? (Can it be baked in afterwards?)
## Try to do away with semicolons and braces

	do
		var c = getchar()
	until c == EOF
		print(c)

	// Actually, like that, it's almost like:

	do
		var c = getchar()
		break if c == EOF
		print(c)

	// Perhaps we should write it like that?

Minor stuff likely to come up

- Fancy literals
- Tuples (is this minor?)
- keyword macros (ptr X, shared_ptr X, ...)
- Probably other things as well
- scope(exit) like 

