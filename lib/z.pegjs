/*
 * Classic example grammar, which recognizes simple arithmetic expressions like
 * "2*(3+4)". The parser generated from this grammar then computes their value.
 * 
 * Modified slightly so whitespace is ok and the initial test.z can be valid Z.
 */

start
	= _ result:additive ';'? _ { return result; }

single_line_comment
	= '//' [^\n]* 

multiline_comment 
	= '/*' comment_content

comment_content
	= '*/'
	/ . comment_content

whitespace_character = 
	[ \f\n\r\t\v]

whitespace "whitespace" =
	( whitespace_character
	/ single_line_comment
	/ multiline_comment
	)

// Optional whitespace
_ = whitespace*

// Mandatory whitespace
__ = whitespace+

additive
	= left:multiplicative _ "+" _ right:additive { return left + right; }
	/ multiplicative

multiplicative
	= left:primary _ "*" _ right:multiplicative { return left * right; }
	/ primary

primary
	= integer
	/ "(" _ additive:additive _ ")" { return additive; }

integer "integer"
	= digits:[0-9]+ { return parseInt(digits.join(""), 10); }

