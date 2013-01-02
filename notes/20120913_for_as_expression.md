# For as expression

You can use `for` (or possibly other looping construct) to generate a list of results:

Instead of:

int[] values;

for x in [1, 2, 3] {
	values.push(x * 2);
}

You could use:

var values = for x in [1, 2, 3] {
	yield x * 2;
}

Instead of yield keyword, possibly allow assignment to a magic value:

var values = for x in [1, 2, 3] {
	result = x * 2;
}

Or just allow the last expression in a block be the the value that is being
collected:

var values = for x in [1, 2, 3] {
	x * 2;
}

So it would generate a list of the same type as what is being iterated on.

Unlike in CoffeeScript, for loops wouldn't automatically generate values, and
there's no implicit `return`. This is to avoid unnecessary work in cases like:

do_something(a, b, c) {
	if (something) {
		for x in [a, b, c]
			print(x);
	} else {
		for x in [a, b, c]
			print(x * 2);
	}
}

If we leave out the return type of this template, the compiler would have to
assume that it returns [int], (in the hypothetical case that print() would
return an int for some reason) and it would have to construct them even though
the results are not used.

The rationale for this is that unlike coffeescript, which encourages functional
programming style, Z actually encourages imperative style, `void` functions,
modifying variables when it makes sense from a performance or understandability
standpoint and doing things just out of the sheer joy of making side effects
happen (in this case, I/O).

Does this rule out being able to use the value of `if` or `switch`? For
example:

var result = if true {
	1;
} else {
	2;
}

It would be peculiar if in these cases, the return value was always constructed. Or would it?

Perhaps we need the concept of expression's value being used.

An expression is used if:
	- it is the expression in `var <variable> = <expression>`
	- it is the last expression inside a block, and the block is used (for example, it's part of a for loop or an if expression that is used)
	- it is the last expression inside a function, and the function has a return type
	- it is the expression in `yield <expression>`

In these cases, if the expression is a loop construct (a `for`, or possibly
another kind of loop; a `while` might come into question as well), its value
will be generated.

(Is this getting too complex? Maybe skip the comprehensions for now before more
important matters are tackled. We can live without them, by just pushing them
into a list; plus we get more control (what kind of list, etc.) that way.)

