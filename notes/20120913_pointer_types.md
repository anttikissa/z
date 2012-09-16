# Pointer types

It's likely that the `&int` syntax to mean 'pointer to int' won't work.

Consider the case where you want to store pointers to objects (and objects) in an array:

If & binds tighter then [], we'd have to say:

	// This is ok
	&Person[] p_persons = get_p_persons();
	&Person p_to_first = p_persons[0];

	// if * binds tighter than [] as well
	Person first = *(p_persons[0]); 
	// If [] binds tighter than * (ok, but illogical; & should be the same as *)
	Person first = *p_persons[0]; 

	// and this is not so ok: 

	Person[] persons = get_persons();
	&Person p_to_first = &(persons[0]));

If [] binds tighter than &, we'd have to declare:

	(&Person)[] persons = get_p_persons();

which is not good either.

So likely the syntax `int*` would have to suffice for a pointer.

	// This is ok
	Person*[] p_persons = get_p_persons();
	Person* p_first = p_persons[0];
	Person first = *p_persons[0]; // postfix [] binds tighter than prefix * 

	// This likewise
	Person[] persons = get_persons();
	Person* p = &persons[0]; // postfix [] binds tighter than prefix &

	// Sometimes a function might want to take a pointer to an array:
	f(Person[]* p) { (*p).push(Person("Antti")); }
	
	// The only thing where this might fail is when we'd apply qualifiers to the
	// outermost thing (assuming readonly):
	readonly Person* p; // the pointer is readonly
	(readonly Person)* p; // points to a readonly

	// In this case, we could use the prefix 'ptr' keyword:
	f(ptr readonly Person p)

	// But this might not work ideally in all situations:
	(ptr Person)[] p_persons = get_p_persons();

	// I wonder if the C++ syntax works better:
	ptr<Person>[] p_persons = get_p_persons();

	// Now there might be multiple syntaxes for the same thing:
	ptr Person p;
	Person* p;
	ptr<Person> p;

	// We're going to have smart pointers so it makes sense:
	shared<Person> p;
	shared Person p; // keyword shortcut
	single<Person> p;
	single Person p; // keyword shortcut

	// Depending on the decided syntax, we might be able to parameterize the
	// pointers with normal parentheses as well:

	ptr(Person)[] p_persons = get_p_persons();
	single(Person)[] my_persons = get_em();

It is left to be seen whether parameterized functions are possible (at least in
similar capacity as with C++) with this syntax, or if we have to replace them
with templates, and if that is possible at all.

TODO references

