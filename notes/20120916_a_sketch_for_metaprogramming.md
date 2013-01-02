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
		
	}

This is one possible way to define `with`, both its syntax extension (not in too
readable form) and its body with one declaration. `assignment_expr` and `stmt`
refer to grammar productions that are used to parse the code following `with`


