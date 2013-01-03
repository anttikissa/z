# Compile-time metaprogramming, that is

Will be likely implemented last, after the important stuff is done with, as an
icing on the cake.

## Macros 

For instance, how to implement the `with` macro described in the "grand plan"
document?

	with (foo = bar) {
		something;
	}

=>

	{
		var orig = foo;
		foo = bar;
		something;
		foo = orig;
	}

(with names & scopes arranged such that the name `orig` is unique and thus won't
conflict with anything in `something`)

	macro with '(' assignment_expr(lhs, rhs) ')' stmt(body) {
		var id = gensym('orig');
		return `{
			var $id = $rhs;
			$lhs = $rhs;
			$body;
			$lhs = $id;
		};
	}

This is one possible way to define `with`, both its syntax extension (not in too
readable form) and its body with one declaration. `assignment_expr` and `stmt`
refer to grammar productions that are used to parse the code following `with`,
and `lhs`, `rhs` and `body` are variables that are bound to their parts'
compile-time representations.

Another way would be to separate the code generation from the syntax extension I
expect many macros to resemble function calls and therefore the standard
function call syntax might be enough for them.  On the other call, I expect that
many macros will resemble native statements, like the above:

	twice {
		...
	}

	repeat (n) {
		...
	}

	until (cond) {
		...
	}

Thus it might be beneficial to make use of that syntax extension.

I'd like a way to specify macro syntax to be similar to how the language itself
defines its own constructs.  (And eventually, to implement as many with macros
as possible.)

Also, make it possible (and easy, and readable) to pick things apart
programmatically -- suppose we have `assignment_expr a` resembling the code 
`results[1] = get_value()`. We want to say something like

	var target = a.lhs;
	var expr = a.rhs;

which works, but can it be made more readable, taking into account that a
represents something that looks like `x = y`?  Perhaps this:

	`$target = $expr` = a;

(Similar to destructuring assignment in JavaScript and other languages.)
Although I'm not sure that's really a big improvement.  Perhaps in more complex
statements.

	`$type $name = $value;` = definition;

Then again, it might break down with more complex statements:

	`switch ($expr) { $contents }` = switch_stmt;

How to pick out all of the different branches from $contents easily?



