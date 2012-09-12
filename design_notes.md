# Random things

If pegjs doesn't make it simple to ignore whitespace everywhere, we might want
to make the language somewhat whitespace-aware.

For example,

	if (f) {
	}

would be fine, however

	if(f) {
	}

or

	if (f){
	}

wouldn't.

