/* YACC parser for C syntax.
   Copyright (C) 1987, 1988, 1989, 1992 Free Software Foundation, Inc.
   Objective-C extensions by s.naroff.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */


/* To whomever it may concern: I have heard that such a thing was once
written by AT&T, but I have never seen it.  */

%expect 36

/* These are the 8 conflicts you should get in parse.output;
   the state numbers may vary if minor changes in the grammar are made.

State 41 contains 1 shift/reduce conflict.  (Two ways to recover from error.)
State 92 contains 1 shift/reduce conflict.  (Two ways to recover from error.)
State 99 contains 1 shift/reduce conflict.  (Two ways to recover from error.)
State 103 contains 1 shift/reduce conflict.  (Two ways to recover from error.)
State 119 contains 1 shift/reduce conflict.  (See comment at component_decl.)
State 183 contains 1 shift/reduce conflict.  (Two ways to recover from error.)
State 193 contains 1 shift/reduce conflict.  (Two ways to recover from error.)
State 199 contains 1 shift/reduce conflict.  (Two ways to recover from error.)
*/

%{
#include <stdio.h>
#include <errno.h>
#include <setjmp.h>

#include "config.h"
#include "tree.h"
#include "input.h"
#include "c-lex.h"
#include "c-tree.h"
#include "flags.h"

#include "objc-actions.h"

#ifndef errno
extern int errno;
#endif

void yyerror ();

/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1
%}

%start program

%union {long itype; tree ttype; enum tree_code code;
	char *filename; int lineno; }

/* All identifiers that are not reserved words
   and are not declared typedefs in the current block */
%token IDENTIFIER

/* All identifiers that are declared typedefs in the current block.
   In some contexts, they are treated just like IDENTIFIER,
   but they can also serve as typespecs in declarations.  */
%token TYPENAME

/* Reserved words that specify storage class.
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token SCSPEC

/* Reserved words that specify type.
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token TYPESPEC

/* Reserved words that qualify type: "const" or "volatile".
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token TYPE_QUAL

/* Character or numeric constants.
   yylval is the node for the constant.  */
%token CONSTANT

/* String constants in raw form.
   yylval is a STRING_CST node.  */
%token STRING

/* "...", used for functions with variable arglists.  */
%token ELLIPSIS

/* the reserved words */
/* SCO include files test "ASM", so use something else. */
%token SIZEOF ENUM STRUCT UNION IF ELSE WHILE DO FOR SWITCH CASE DEFAULT
%token BREAK CONTINUE RETURN GOTO ASM_KEYWORD TYPEOF ALIGNOF ALIGN
%token ATTRIBUTE EXTENSION LABEL

/* Add precedence rules to solve dangling else s/r conflict */
%nonassoc IF
%nonassoc ELSE

/* Define the operator tokens and their precedences.
   The value is an integer because, if used, it is the tree code
   to use in the expression made from the operator.  */

%right <code> ASSIGN '='
%right <code> '?' ':'
%left <code> OROR
%left <code> ANDAND
%left <code> '|'
%left <code> '^'
%left <code> '&'
%left <code> EQCOMPARE
%left <code> ARITHCOMPARE
%left <code> LSHIFT RSHIFT
%left <code> '+' '-'
%left <code> '*' '/' '%'
%right <code> UNARY PLUSPLUS MINUSMINUS
%left HYPERUNARY
%left <code> POINTSAT '.' '(' '['

/* the Objective-C keywords */
%token INTERFACE IMPLEMENTATION END SELECTOR DEFS ENCODE
%token CLASSNAME PUBLIC


%type <code> unop

%type <ttype> identifier IDENTIFIER TYPENAME CONSTANT expr nonnull_exprlist exprlist
%type <ttype> expr_no_commas cast_expr unary_expr primary string STRING
%type <ttype> typed_declspecs reserved_declspecs
%type <ttype> typed_typespecs reserved_typespecquals
%type <ttype> declmods typespec typespecqual_reserved
%type <ttype> SCSPEC TYPESPEC TYPE_QUAL nonempty_type_quals maybe_type_qual
%type <ttype> initdecls notype_initdecls initdcl notype_initdcl
%type <ttype> init initlist maybeasm
%type <ttype> asm_operands nonnull_asm_operands asm_operand asm_clobbers
%type <ttype> maybe_attribute attribute_list attrib

%type <ttype> compstmt

%type <ttype> declarator
%type <ttype> notype_declarator after_type_declarator
%type <ttype> parm_declarator

%type <ttype> structsp component_decl_list component_decl_list2
%type <ttype> component_decl components component_declarator
%type <ttype> enumlist enumerator
%type <ttype> typename absdcl absdcl1 type_quals
%type <ttype> xexpr parms parm identifiers

%type <ttype> parmlist parmlist_1 parmlist_2
%type <ttype> parmlist_or_identifiers parmlist_or_identifiers_1

%type <itype> setspecs

%type <filename> save_filename
%type <lineno> save_lineno

/* the Objective-C nonterminals */

%type <ttype> ivar_decl_list ivar_decls ivar_decl ivars ivar_declarator
%type <ttype> methoddecl unaryselector keywordselector selector
%type <ttype> keyworddecl receiver objcmessageexpr messageargs
%type <ttype> keywordexpr keywordarglist keywordarg
%type <ttype> myparms myparm optparmlist reservedwords objcselectorexpr
%type <ttype> selectorarg keywordnamelist keywordname objcencodeexpr
%type <ttype> CLASSNAME

%{
/* Number of statements (loosely speaking) seen so far.  */
static int stmt_count;

/* Input file and line number of the end of the body of last simple_if;
   used by the stmt-rule immediately after simple_if returns.  */
static char *if_stmt_file;
static int if_stmt_line;

/* List of types and structure classes of the current declaration.  */
static tree current_declspecs;

/* Stack of saved values of current_declspecs.  */
static tree declspec_stack;

/* 1 if we explained undeclared var errors.  */
static int undeclared_variable_notice;

/* Objective-C specific information */

tree objc_interface_context;
tree objc_implementation_context;
tree objc_method_context;
tree objc_ivar_chain;
tree objc_ivar_context;
enum tree_code objc_inherit_code;
int objc_receiver_context;
int objc_public_flag;

/* Tell yyparse how to print a token's value, if yydebug is set.  */

#define YYPRINT(FILE,YYCHAR,YYLVAL) yyprint(FILE,YYCHAR,YYLVAL)
extern void yyprint ();
%}

%%
program: /* empty */
		{ if (pedantic)
		    pedwarn ("ANSI C forbids an empty source file");
		  objc_finish (); }
	| extdefs
		{ objc_finish (); }
	;

/* the reason for the strange actions in this rule
 is so that notype_initdecls when reached via datadef
 can find a valid list of type and sc specs in $0. */

extdefs:
	{$<ttype>$ = NULL_TREE; } extdef
	| extdefs {$<ttype>$ = NULL_TREE; } extdef
	;

extdef:
	fndef
	| datadef
	| objcdef
	| ASM_KEYWORD '(' string ')' ';'
		{ if (pedantic)
		    pedwarn ("ANSI C forbids use of `asm' keyword");
		  if (TREE_CHAIN ($3)) $3 = combine_strings ($3);
		  assemble_asm ($3); }
	;

datadef:
	  setspecs notype_initdecls ';'
		{ if (pedantic)
		    error ("ANSI C forbids data definition with no type or storage class");
		  else if (!flag_traditional)
		    warning ("data definition has no type or storage class"); }
        | declmods setspecs notype_initdecls ';'
	  {}
	| typed_declspecs setspecs initdecls ';'
	  {}
        | declmods ';'
	  { error ("empty declaration"); }
	| typed_declspecs ';'
	  { shadow_tag ($1); }
	| error ';'
	| error '}'
	| ';'
		{ if (pedantic)
		    pedwarn ("ANSI C does not allow extra `;' outside of a function"); }
	;

fndef:
	  typed_declspecs setspecs declarator
		{ if (! start_function ($1, $3, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
	  xdecls
		{ store_parm_decls (); }
	  compstmt_or_error
		{ finish_function (0); }
	| typed_declspecs setspecs declarator error
		{ }
	| declmods setspecs notype_declarator
		{ if (! start_function ($1, $3, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
	  xdecls
		{ store_parm_decls (); }
	  compstmt_or_error
		{ finish_function (0); }
	| declmods setspecs notype_declarator error
		{ }
	| setspecs notype_declarator
		{ if (! start_function (0, $2, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
	  xdecls
		{ store_parm_decls (); }
	  compstmt_or_error
		{ finish_function (0); }
	| setspecs notype_declarator error
		{ }
	;

identifier:
	IDENTIFIER
	| TYPENAME
        | CLASSNAME
		{ $$ = CLASS_NAME ($1); }
	;

unop:     '&'
		{ $$ = ADDR_EXPR; }
	| '-'
		{ $$ = NEGATE_EXPR; }
	| '+'
		{ $$ = CONVERT_EXPR; }
	| PLUSPLUS
		{ $$ = PREINCREMENT_EXPR; }
	| MINUSMINUS
		{ $$ = PREDECREMENT_EXPR; }
	| '~'
		{ $$ = BIT_NOT_EXPR; }
	| '!'
		{ $$ = TRUTH_NOT_EXPR; }
	;

expr:	nonnull_exprlist
		{ $$ = build_compound_expr ($1); }
	;

exprlist:
	  /* empty */
		{ $$ = NULL_TREE; }
	| nonnull_exprlist
	;

nonnull_exprlist:
	expr_no_commas
		{ $$ = build_tree_list (NULL_TREE, $1); }
	| nonnull_exprlist ',' expr_no_commas
		{ chainon ($1, build_tree_list (NULL_TREE, $3)); }
	;

unary_expr:
	primary
	| '*' cast_expr   %prec UNARY
		{ $$ = build_indirect_ref ($2, "unary *"); }
	/* __extension__ turns off -pedantic for following primary.  */
	| EXTENSION
		{ $<itype>1 = pedantic;
		  pedantic = 0; }
	  cast_expr	  %prec UNARY
		{ $$ = $3;
		  pedantic = $<itype>1; }
	| unop cast_expr  %prec UNARY
		{ $$ = build_unary_op ($1, $2, 0); }
	/* Refer to the address of a label as a pointer.  */
	| ANDAND identifier
		{ tree label = lookup_label ($2);
		  TREE_USED (label) = 1;
		  $$ = build1 (ADDR_EXPR, ptr_type_node, label);
		  TREE_CONSTANT ($$) = 1; }
/* This seems to be impossible on some machines, so let's turn it off.
	| '&' ELLIPSIS
		{ tree types = TYPE_ARG_TYPES (TREE_TYPE (current_function_decl));
		  $$ = error_mark_node;
		  if (TREE_VALUE (tree_last (types)) == void_type_node)
		    error ("`&...' used in function with fixed number of arguments");
		  else
		    {
		      if (pedantic)
			pedwarn ("ANSI C forbids `&...'");
		      $$ = tree_last (DECL_ARGUMENTS (current_function_decl));
		      $$ = build_unary_op (ADDR_EXPR, $$, 0);
		    } }
*/
	| SIZEOF unary_expr  %prec UNARY
		{ if (TREE_CODE ($2) == COMPONENT_REF
		      && DECL_BIT_FIELD (TREE_OPERAND ($2, 1)))
		    error ("`sizeof' applied to a bit-field");
		  $$ = c_sizeof (TREE_TYPE ($2)); }
	| SIZEOF '(' typename ')'  %prec HYPERUNARY
		{ $$ = c_sizeof (groktypename ($3)); }
	| ALIGNOF unary_expr  %prec UNARY
		{ $$ = c_alignof_expr ($2); }
	| ALIGNOF '(' typename ')'  %prec HYPERUNARY
		{ $$ = c_alignof (groktypename ($3)); }
	;

cast_expr:
	unary_expr
	| '(' typename ')' cast_expr  %prec UNARY
		{ tree type = groktypename ($2);
		  $$ = build_c_cast (type, $4); }
	| '(' typename ')' '{' initlist maybecomma '}'  %prec UNARY
		{ tree type = groktypename ($2);
		  if (pedantic)
		    pedwarn ("ANSI C forbids constructor expressions");
		  $$ = digest_init (type, build_nt (CONSTRUCTOR, NULL_TREE, nreverse ($5)), 0, 0, 0);
		  if (TREE_CODE (type) == ARRAY_TYPE && TYPE_SIZE (type) == 0)
		    {
		      int failure = complete_array_type (type, $$, 1);
		      if (failure)
			abort ();
		    }
		}
	;

expr_no_commas:
	  cast_expr
	| expr_no_commas '+' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas '-' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas '*' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas '/' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas '%' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas LSHIFT expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas RSHIFT expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas ARITHCOMPARE expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas EQCOMPARE expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas '&' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas '|' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas '^' expr_no_commas
		{ $$ = parser_build_binary_op ($2, $1, $3); }
	| expr_no_commas ANDAND expr_no_commas
		{ $$ = parser_build_binary_op (TRUTH_ANDIF_EXPR, $1, $3); }
	| expr_no_commas OROR expr_no_commas
		{ $$ = parser_build_binary_op (TRUTH_ORIF_EXPR, $1, $3); }
	| expr_no_commas '?' xexpr ':' expr_no_commas
		{ $$ = build_conditional_expr ($1, $3, $5); }
	| expr_no_commas '=' expr_no_commas
		{ $$ = build_modify_expr ($1, NOP_EXPR, $3); }
	| expr_no_commas ASSIGN expr_no_commas
		{ $$ = build_modify_expr ($1, $2, $3); }
	;

primary:
	IDENTIFIER
		{
		  tree context;

		  $$ = lastiddecl;
		  if (!$$ || $$ == error_mark_node)
		    {
		      if (yychar == YYEMPTY)
			yychar = YYLEX;
		      if (yychar == '(')
			{
			  if (objc_receiver_context
			      && ! (objc_receiver_context
				    && strcmp (IDENTIFIER_POINTER ($1), "super")))
			    /* we have a message to super */
			    $$ = get_super_receiver ();
			  else if (objc_method_context
				   && is_ivar (objc_ivar_chain, $1))
			    $$ = build_ivar_reference ($1);
			  else
			    {
			      /* Ordinary implicit function declaration.  */
			      $$ = implicitly_declare ($1);
			      assemble_external ($$);
			      TREE_USED ($$) = 1;
			    }
			}
		      else if (current_function_decl == 0)
			{
			  error ("`%s' undeclared, outside of functions",
				 IDENTIFIER_POINTER ($1));
			  $$ = error_mark_node;
			}
		      else
			{
		          if (objc_receiver_context
			      && ! (objc_receiver_context
				    && strcmp (IDENTIFIER_POINTER ($1), "super")))
			    /* we have a message to super */
			    $$ = get_super_receiver ();
			  else if (objc_method_context
				   && is_ivar (objc_ivar_chain, $1))
			    $$ = build_ivar_reference ($1);
			  else
			    {
			      if (IDENTIFIER_GLOBAL_VALUE ($1) != error_mark_node
				  || IDENTIFIER_ERROR_LOCUS ($1) != current_function_decl)
				{
				  error ("`%s' undeclared (first use this function)",
					 IDENTIFIER_POINTER ($1));

				  if (! undeclared_variable_notice)
				    {
				      error ("(Each undeclared identifier is reported only once");
				      error ("for each function it appears in.)");
				      undeclared_variable_notice = 1;
				    }
				}
			      $$ = error_mark_node;
			      /* Prevent repeated error messages.  */
			      IDENTIFIER_GLOBAL_VALUE ($1) = error_mark_node;
			      IDENTIFIER_ERROR_LOCUS ($1) = current_function_decl;
		            }
			}
		    }
		  else
		    {
		      if (! TREE_USED ($$))
			{
			  if (TREE_EXTERNAL ($$))
			    assemble_external ($$);
			  TREE_USED ($$) = 1;
			}
		      /* we have a definition - still check if iVariable */

		      if (!objc_receiver_context
			  || (objc_receiver_context
			      && strcmp (IDENTIFIER_POINTER ($1), "super")))
                        {
			  if (objc_method_context
			      && is_ivar (objc_ivar_chain, $1))
                            {
                              if (IDENTIFIER_LOCAL_VALUE ($1))
                                warning ("local declaration of `%s' hides instance variable",
	                                 IDENTIFIER_POINTER ($1));
                              else
                                $$ = build_ivar_reference ($1);
                            }
			}
                      else /* we have a message to super */
		        $$ = get_super_receiver ();
		    }

		  if (TREE_CODE ($$) == CONST_DECL)
		    $$ = DECL_INITIAL ($$);
		}
	| CONSTANT
	| string
		{ $$ = combine_strings ($1); }
	| '(' expr ')'
		{ char class = TREE_CODE_CLASS (TREE_CODE ($2));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ($2, ERROR_MARK);
		  $$ = $2; }
	| '(' error ')'
		{ $$ = error_mark_node; }
	| '('
		{ if (current_function_decl == 0)
		    {
		      error ("braced-group within expression allowed only inside a function");
		      YYERROR;
		    }
		  /* We must force a BLOCK for this level
		     so that, if it is not expanded later,
		     there is a way to turn off the entire subtree of blocks
		     that are contained in it.  */
		  keep_next_level ();
		  push_label_level ();
		  $<ttype>$ = expand_start_stmt_expr (); }
	  compstmt ')'
		{ tree rtl_exp;
		  if (pedantic)
		    pedwarn ("ANSI C forbids braced-groups within expressions");
		  pop_label_level ();
		  rtl_exp = expand_end_stmt_expr ($<ttype>2);
		  /* The statements have side effects, so the group does.  */
		  TREE_SIDE_EFFECTS (rtl_exp) = 1;

		  /* Make a BIND_EXPR for the BLOCK already made.  */
		  $$ = build (BIND_EXPR, TREE_TYPE (rtl_exp),
			      NULL_TREE, rtl_exp, $3);
		}
	| primary '(' exprlist ')'   %prec '.'
		{ $$ = build_function_call ($1, $3); }
	| primary '[' expr ']'   %prec '.'
		{ $$ = build_array_ref ($1, $3); }
	| primary '.' identifier
		{
                  if (doing_objc_thang)
                    {
		      if (is_public ($1, $3))
			$$ = build_component_ref ($1, $3);
		      else
			$$ = error_mark_node;
		    }
                  else
                    $$ = build_component_ref ($1, $3);
		}
	| primary POINTSAT identifier
		{
                  tree anExpr = build_indirect_ref ($1, "->");

                  if (doing_objc_thang)
                    {
		      if (is_public (anExpr, $3))
			$$ = build_component_ref (anExpr, $3);
		      else
			$$ = error_mark_node;
		    }
                  else
                    $$ = build_component_ref (anExpr, $3);
		}
	| primary PLUSPLUS
		{ $$ = build_unary_op (POSTINCREMENT_EXPR, $1, 0); }
	| primary MINUSMINUS
		{ $$ = build_unary_op (POSTDECREMENT_EXPR, $1, 0); }
	| objcmessageexpr
		{ $$ = build_message_expr ($1); }
	| objcselectorexpr
		{ $$ = build_selector_expr ($1); }
	| objcencodeexpr
		{ $$ = build_encode_expr ($1); }
	;

/* Produces a STRING_CST with perhaps more STRING_CSTs chained onto it.  */
string:
	  STRING
	| string STRING
		{ $$ = chainon ($1, $2); }
	;

xdecls:
	/* empty */
	| decls
	| decls ELLIPSIS
		/* ... is used here to indicate a varargs function.  */
		{ c_mark_varargs ();
		  if (pedantic)
		    pedwarn ("ANSI C does not permit use of `varargs.h'"); }
	;

/* This combination which saves a lineno before a decl
   is the normal thing to use, rather than decl itself.
   This is to avoid shift/reduce conflicts in contexts
   where statement labels are allowed.  */
lineno_decl:
	  save_filename save_lineno decl
		{ }
	;

decls:
	lineno_decl
	| errstmt
	| decls lineno_decl
	| lineno_decl errstmt
	;

/* records the type and storage class specs to use for processing
   the declarators that follow.
   Maintains a stack of outer-level values of current_declspecs,
   for the sake of parm declarations nested in function declarators.  */
setspecs: /* empty */
		{ $$ = suspend_momentary ();
		  pending_xref_error ();
		  declspec_stack = tree_cons (0, current_declspecs,
					      declspec_stack);
		  current_declspecs = $<ttype>0; }
	;

decl:
	typed_declspecs setspecs initdecls ';'
		{ current_declspecs = TREE_VALUE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ($2); }
	| declmods setspecs notype_initdecls ';'
		{ current_declspecs = TREE_VALUE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ($2); }
	| typed_declspecs setspecs nested_function
		{ current_declspecs = TREE_VALUE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ($2); }
	| declmods setspecs notype_nested_function
		{ current_declspecs = TREE_VALUE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ($2); }
	| typed_declspecs ';'
		{ shadow_tag ($1); }
	| declmods ';'
		{ pedwarn ("empty declaration"); }
	;

/* Declspecs which contain at least one type specifier or typedef name.
   (Just `const' or `volatile' is not enough.)
   A typedef'd name following these is taken as a name to be declared.  */

typed_declspecs:
	  typespec reserved_declspecs
		{ $$ = tree_cons (NULL_TREE, $1, $2); }
	| declmods typespec reserved_declspecs
		{ $$ = chainon ($3, tree_cons (NULL_TREE, $2, $1)); }
	;

reserved_declspecs:  /* empty */
		{ $$ = NULL_TREE; }
	| reserved_declspecs typespecqual_reserved
		{ $$ = tree_cons (NULL_TREE, $2, $1); }
	| reserved_declspecs SCSPEC
		{ $$ = tree_cons (NULL_TREE, $2, $1); }
	;

/* List of just storage classes and type modifiers.
   A declaration can start with just this, but then it cannot be used
   to redeclare a typedef-name.  */

declmods:
	  TYPE_QUAL
		{ $$ = tree_cons (NULL_TREE, $1, NULL_TREE); }
	| SCSPEC
		{ $$ = tree_cons (NULL_TREE, $1, NULL_TREE); }
	| declmods TYPE_QUAL
		{ $$ = tree_cons (NULL_TREE, $2, $1); }
	| declmods SCSPEC
		{ $$ = tree_cons (NULL_TREE, $2, $1); }
	;


/* Used instead of declspecs where storage classes are not allowed
   (that is, for typenames and structure components).
   Don't accept a typedef-name if anything but a modifier precedes it.  */

typed_typespecs:
	  typespec reserved_typespecquals
		{ $$ = tree_cons (NULL_TREE, $1, $2); }
	| nonempty_type_quals typespec reserved_typespecquals
		{ $$ = chainon ($3, tree_cons (NULL_TREE, $2, $1)); }
	;

reserved_typespecquals:  /* empty */
		{ $$ = NULL_TREE; }
	| reserved_typespecquals typespecqual_reserved
		{ $$ = tree_cons (NULL_TREE, $2, $1); }
	;

/* A typespec (but not a type qualifier).
   Once we have seen one of these in a declaration,
   if a typedef name appears then it is being redeclared.  */

typespec: TYPESPEC
	| structsp
	| TYPENAME
        | CLASSNAME
		{ $$ = get_static_reference ($1); }
	| TYPEOF '(' expr ')'
		{ $$ = TREE_TYPE ($3);
		  if (pedantic)
		    pedwarn ("ANSI C forbids `typeof'"); }
	| TYPEOF '(' typename ')'
		{ $$ = groktypename ($3);
		  if (pedantic)
		    pedwarn ("ANSI C forbids `typeof'"); }
	;

/* A typespec that is a reserved word, or a type qualifier.  */

typespecqual_reserved: TYPESPEC
	| TYPE_QUAL
	| structsp
	;

initdecls:
	initdcl
	| initdecls ',' initdcl
	;

notype_initdecls:
	notype_initdcl
	| notype_initdecls ',' initdcl
	;

maybeasm:
	  /* empty */
		{ $$ = NULL_TREE; }
	| ASM_KEYWORD '(' string ')'
		{ if (TREE_CHAIN ($3)) $3 = combine_strings ($3);
		  $$ = $3;
		  if (pedantic)
		    pedwarn ("ANSI C forbids use of `asm' keyword");
		}
	;

initdcl:
	  declarator maybeasm maybe_attribute '='
		{ $<ttype>$ = start_decl ($1, current_declspecs, 1); }
	  init
/* Note how the declaration of the variable is in effect while its init is parsed! */
		{ decl_attributes ($<ttype>5, $3);
		  finish_decl ($<ttype>5, $6, $2); }
	| declarator maybeasm maybe_attribute
		{ tree d = start_decl ($1, current_declspecs, 0);
		  decl_attributes (d, $3);
		  finish_decl (d, NULL_TREE, $2); }
	;

notype_initdcl:
	  notype_declarator maybeasm maybe_attribute '='
		{ $<ttype>$ = start_decl ($1, current_declspecs, 1); }
	  init
/* Note how the declaration of the variable is in effect while its init is parsed! */
		{ decl_attributes ($<ttype>5, $3);
		  finish_decl ($<ttype>5, $6, $2); }
	| notype_declarator maybeasm maybe_attribute
		{ tree d = start_decl ($1, current_declspecs, 0);
		  decl_attributes (d, $3);
		  finish_decl (d, NULL_TREE, $2); }
	;
/* the * rules are dummies to accept the Apollo extended syntax
   so that the header files compile. */
maybe_attribute:
    /* empty */
		{ $$ = NULL_TREE; }
    | ATTRIBUTE '(' '(' attribute_list ')' ')'
		{ $$ = $4; }
    ;

attribute_list
    : attrib
	{ $$ = tree_cons (NULL_TREE, $1, NULL_TREE); }
    | attribute_list ',' attrib
	{ $$ = tree_cons (NULL_TREE, $3, $1); }
    ;

attrib
    : IDENTIFIER
	{ warning ("`%s' attribute directive ignored",
		   IDENTIFIER_POINTER ($1));
	  $$ = $1; }
    | IDENTIFIER '(' CONSTANT ')'
	{ /* if not "aligned(n)", then issue warning */
	  if (strcmp (IDENTIFIER_POINTER ($1), "aligned") != 0
	      || TREE_CODE ($3) != INTEGER_CST)
	    {
	      warning ("`%s' attribute directive ignored",
		       IDENTIFIER_POINTER ($1));
	      $$ = $1;
	    }
	  else
	    $$ = tree_cons ($1, $3); }
    | IDENTIFIER '(' IDENTIFIER ',' CONSTANT ',' CONSTANT ')'
	{ /* if not "format(...)", then issue warning */
	  if (strcmp (IDENTIFIER_POINTER ($1), "format") != 0
	      || TREE_CODE ($5) != INTEGER_CST
	      || TREE_CODE ($7) != INTEGER_CST)
	    {
	      warning ("`%s' attribute directive ignored",
		       IDENTIFIER_POINTER ($1));
	      $$ = $1;
	    }
	  else
	    $$ = tree_cons ($1, tree_cons ($3, tree_cons ($5, $7))); }
    ;

init:
	expr_no_commas
	| '{' '}'
		{ $$ = build_nt (CONSTRUCTOR, NULL_TREE, NULL_TREE);
		  if (pedantic)
		    pedwarn ("ANSI C forbids empty initializer braces"); }
	| '{' initlist '}'
		{ $$ = build_nt (CONSTRUCTOR, NULL_TREE, nreverse ($2)); }
	| '{' initlist ',' '}'
		{ $$ = build_nt (CONSTRUCTOR, NULL_TREE, nreverse ($2)); }
	| error
		{ $$ = NULL_TREE; }
	;

/* This chain is built in reverse order,
   and put in forward order where initlist is used.  */
initlist:
	  init
		{ $$ = build_tree_list (NULL_TREE, $1); }
	| initlist ',' init
		{ $$ = tree_cons (NULL_TREE, $3, $1); }
	/* These are for labeled elements.  */
	| '[' expr_no_commas ']' init
		{ $$ = build_tree_list ($2, $4); }
	| initlist ',' CASE expr_no_commas ':' init
		{ $$ = tree_cons ($4, $6, $1); }
	| identifier ':' init
		{ $$ = build_tree_list ($1, $3); }
	| initlist ',' identifier ':' init
		{ $$ = tree_cons ($3, $5, $1); }
	;

nested_function:
	  declarator
		{ push_c_function_context ();
		  if (! start_function (current_declspecs, $1, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function ();
		  store_parm_decls (); }
/* This used to use compstmt_or_error.
   That caused a bug with input `f(g) int g {}',
   where the use of YYERROR1 above caused an error
   which then was handled by compstmt_or_error.
   There followed a repeated execution of that same rule,
   which called YYERROR1 again, and so on.  */
	  compstmt
		{ finish_function (1);
		  pop_c_function_context (); }
	;

notype_nested_function:
	  notype_declarator
		{ push_c_function_context ();
		  if (! start_function (current_declspecs, $1, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function ();
		  store_parm_decls (); }
/* This used to use compstmt_or_error.
   That caused a bug with input `f(g) int g {}',
   where the use of YYERROR1 above caused an error
   which then was handled by compstmt_or_error.
   There followed a repeated execution of that same rule,
   which called YYERROR1 again, and so on.  */
	  compstmt
		{ finish_function (1);
		  pop_c_function_context (); }
	;

/* Any kind of declarator (thus, all declarators allowed
   after an explicit typespec).  */

declarator:
	  after_type_declarator
	| notype_declarator
	;

/* A declarator that is allowed only after an explicit typespec.  */

after_type_declarator:
	  '(' after_type_declarator ')'
		{ $$ = $2; }
	| after_type_declarator '(' parmlist_or_identifiers  %prec '.'
		{ $$ = build_nt (CALL_EXPR, $1, $3, NULL_TREE); }
/*	| after_type_declarator '(' error ')'  %prec '.'
		{ $$ = build_nt (CALL_EXPR, $1, NULL_TREE, NULL_TREE);
		  poplevel (0, 0, 0); }  */
	| after_type_declarator '[' expr ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, $3); }
	| after_type_declarator '[' ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, NULL_TREE); }
	| '*' type_quals after_type_declarator  %prec UNARY
		{ $$ = make_pointer_declarator ($2, $3); }
	| TYPENAME
	;

/* Kinds of declarator that can appear in a parameter list
   in addition to notype_declarator.  This is like after_type_declarator
   but does not allow a typedef name in parentheses as an identifier
   (because it would conflict with a function with that typedef as arg).  */

parm_declarator:
	  parm_declarator '(' parmlist_or_identifiers  %prec '.'
		{ $$ = build_nt (CALL_EXPR, $1, $3, NULL_TREE); }
/*	| parm_declarator '(' error ')'  %prec '.'
		{ $$ = build_nt (CALL_EXPR, $1, NULL_TREE, NULL_TREE);
		  poplevel (0, 0, 0); }  */
	| parm_declarator '[' expr ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, $3); }
	| parm_declarator '[' ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, NULL_TREE); }
	| '*' type_quals parm_declarator  %prec UNARY
		{ $$ = make_pointer_declarator ($2, $3); }
	| TYPENAME
	;

/* A declarator allowed whether or not there has been
   an explicit typespec.  These cannot redeclare a typedef-name.  */

notype_declarator:
	  notype_declarator '(' parmlist_or_identifiers  %prec '.'
		{ $$ = build_nt (CALL_EXPR, $1, $3, NULL_TREE); }
/*	| notype_declarator '(' error ')'  %prec '.'
		{ $$ = build_nt (CALL_EXPR, $1, NULL_TREE, NULL_TREE);
		  poplevel (0, 0, 0); }  */
	| '(' notype_declarator ')'
		{ $$ = $2; }
	| '*' type_quals notype_declarator  %prec UNARY
		{ $$ = make_pointer_declarator ($2, $3); }
	| notype_declarator '[' expr ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, $3); }
	| notype_declarator '[' ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, NULL_TREE); }
	| IDENTIFIER
	;

structsp:
	  STRUCT identifier '{'
		{ $$ = start_struct (RECORD_TYPE, $2);
		  /* Start scope of tag before parsing components.  */
		}
	  component_decl_list '}'
		{ $$ = finish_struct ($<ttype>4, $5);
		  /* Really define the structure.  */
		}
	| STRUCT '{' component_decl_list '}'
		{ $$ = finish_struct (start_struct (RECORD_TYPE, NULL_TREE),
				      $3); }
	| STRUCT identifier
		{ $$ = xref_tag (RECORD_TYPE, $2); }
	| UNION identifier '{'
		{ $$ = start_struct (UNION_TYPE, $2); }
	  component_decl_list '}'
		{ $$ = finish_struct ($<ttype>4, $5); }
	| UNION '{' component_decl_list '}'
		{ $$ = finish_struct (start_struct (UNION_TYPE, NULL_TREE),
				      $3); }
	| UNION identifier
		{ $$ = xref_tag (UNION_TYPE, $2); }
	| ENUM identifier '{'
		{ $<itype>3 = suspend_momentary ();
		  $$ = start_enum ($2); }
	  enumlist maybecomma_warn '}'
		{ $$ = finish_enum ($<ttype>4, nreverse ($5));
		  resume_momentary ($<itype>3); }
	| ENUM '{'
		{ $<itype>2 = suspend_momentary ();
		  $$ = start_enum (NULL_TREE); }
	  enumlist maybecomma_warn '}'
		{ $$ = finish_enum ($<ttype>3, nreverse ($4));
		  resume_momentary ($<itype>2); }
	| ENUM identifier
		{ $$ = xref_tag (ENUMERAL_TYPE, $2); }
	;

maybecomma:
	  /* empty */
	| ','
	;

maybecomma_warn:
	  /* empty */
	| ','
		{ if (pedantic) pedwarn ("comma at end of enumerator list"); }
	;

component_decl_list:
	  component_decl_list2
		{ $$ = $1; }
	| component_decl_list2 component_decl
		{ $$ = chainon ($1, $2);
		  warning ("no semicolon at end of struct or union"); }
	;

component_decl_list2:	/* empty */
		{ $$ = NULL_TREE; }
	| component_decl_list2 component_decl ';'
		{ $$ = chainon ($1, $2); }
	| component_decl_list2 ';'
		{ if (pedantic)
		    warning ("extra semicolon in struct or union specified"); }
	/* foo(sizeof(struct{ @defs(ClassName)})); */
	| DEFS '(' CLASSNAME ')'
		{ $$ = get_class_ivars ($3); }
	;

/* There is a shift-reduce conflict here, because `components' may
   start with a `typename'.  It happens that shifting (the default resolution)
   does the right thing, because it treats the `typename' as part of
   a `typed_typespecs'.

   It is possible that this same technique would allow the distinction
   between `notype_initdecls' and `initdecls' to be eliminated.
   But I am being cautious and not trying it.  */

component_decl:
	  typed_typespecs setspecs components
		{ $$ = $3;
		  current_declspecs = TREE_VALUE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ($2); }
	| typed_typespecs
		{ if (pedantic)
		    pedwarn ("ANSI C forbids member declarations with no members");
		  shadow_tag($1);
		  $$ = NULL_TREE; }
	| nonempty_type_quals setspecs components
		{ $$ = $3;
		  current_declspecs = TREE_VALUE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ($2); }
	| nonempty_type_quals
		{ if (pedantic)
		    pedwarn ("ANSI C forbids member declarations with no members");
		  shadow_tag($1);
		  $$ = NULL_TREE; }
	| error
		{ $$ = NULL_TREE; }
	;

components:
	  component_declarator
	| components ',' component_declarator
		{ $$ = chainon ($1, $3); }
	;

component_declarator:
	  save_filename save_lineno declarator maybe_attribute
		{ $$ = grokfield ($1, $2, $3, current_declspecs, NULL_TREE);
		  decl_attributes ($$, $4); }
	| save_filename save_lineno
	  declarator ':' expr_no_commas maybe_attribute
		{ $$ = grokfield ($1, $2, $3, current_declspecs, $5);
		  decl_attributes ($$, $6); }
	| save_filename save_lineno ':' expr_no_commas
		{ $$ = grokfield ($1, $2, NULL_TREE, current_declspecs, $4); }
	;

/* We chain the enumerators in reverse order.
   They are put in forward order where enumlist is used.
   (The order used to be significant, but no longer is so.
   However, we still maintain the order, just to be clean.)  */

enumlist:
	  enumerator
	| enumlist ',' enumerator
		{ $$ = chainon ($3, $1); }
	;


enumerator:
	  identifier
		{ $$ = build_enumerator ($1, NULL_TREE); }
	| identifier '=' expr_no_commas
		{ $$ = build_enumerator ($1, $3); }
	;

typename:
	typed_typespecs absdcl
		{ $$ = build_tree_list ($1, $2); }
	| nonempty_type_quals absdcl
		{ $$ = build_tree_list ($1, $2); }
	;

absdcl:   /* an absolute declarator */
	/* empty */
		{ $$ = NULL_TREE; }
	| absdcl1
	;

nonempty_type_quals:
	  TYPE_QUAL
		{ $$ = tree_cons (NULL_TREE, $1, NULL_TREE); }
	| nonempty_type_quals TYPE_QUAL
		{ $$ = tree_cons (NULL_TREE, $2, $1); }
	;

type_quals:
	  /* empty */
		{ $$ = NULL_TREE; }
	| type_quals TYPE_QUAL
		{ $$ = tree_cons (NULL_TREE, $2, $1); }
	;

absdcl1:  /* a nonempty absolute declarator */
	  '(' absdcl1 ')'
		{ $$ = $2; }
	  /* `(typedef)1' is `int'.  */
	| '*' type_quals absdcl1  %prec UNARY
		{ $$ = make_pointer_declarator ($2, $3); }
	| '*' type_quals  %prec UNARY
		{ $$ = make_pointer_declarator ($2, NULL_TREE); }
	| absdcl1 '(' parmlist  %prec '.'
		{ $$ = build_nt (CALL_EXPR, $1, $3, NULL_TREE); }
	| absdcl1 '[' expr ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, $3); }
	| absdcl1 '[' ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, $1, NULL_TREE); }
	| '(' parmlist  %prec '.'
		{ $$ = build_nt (CALL_EXPR, NULL_TREE, $2, NULL_TREE); }
	| '[' expr ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, NULL_TREE, $2); }
	| '[' ']'  %prec '.'
		{ $$ = build_nt (ARRAY_REF, NULL_TREE, NULL_TREE); }
	;

/* at least one statement, the first of which parses without error.  */
/* stmts is used only after decls, so an invalid first statement
   is actually regarded as an invalid decl and part of the decls.  */

stmts:
	lineno_stmt
	| stmts lineno_stmt
	| stmts errstmt
	;

xstmts:
	/* empty */
	| stmts
	;

errstmt:  error ';'
	;

pushlevel:  /* empty */
		{ emit_line_note (input_filename, lineno);
		  pushlevel (0);
		  clear_last_expr ();
		  push_momentary ();
		  expand_start_bindings (0);
		  if (objc_method_context)
		    add_objc_decls (); }
	;

/* Read zero or more forward-declarations for labels
   that nested functions can jump to.  */
maybe_label_decls:
	  /* empty */
	| label_decls
		{ if (pedantic)
		    pedwarn ("ANSI C forbids label declarations"); }
	;

label_decls:
	  label_decl
	| label_decls label_decl
	;

label_decl:
	  LABEL identifiers ';'
		{ tree link;
		  for (link = $2; link; link = TREE_CHAIN (link))
		    {
		      tree label = shadow_label (TREE_VALUE (link));
		      C_DECLARED_LABEL_FLAG (label) = 1;
		      declare_nonlocal_label (label);
		    }
		}
	;

/* This is the body of a function definition.
   It causes syntax errors to ignore to the next openbrace.  */

/* allow for: main () { Example *anObject = [Example new]; } */

compstmt_or_error:
	  compstmt
		{}
	| error compstmt
	;

compstmt: '{' '}'
		{ $$ = convert (void_type_node, integer_zero_node); }
	| '{' pushlevel maybe_label_decls decls xstmts '}'
		{ emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), 1, 0);
		  $$ = poplevel (1, 1, 0);
		  pop_momentary (); }
	| '{' pushlevel maybe_label_decls error '}'
		{ emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  $$ = poplevel (kept_level_p (), 0, 0);
		  pop_momentary (); }
	| '{' pushlevel maybe_label_decls stmts '}'
		{ emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  $$ = poplevel (kept_level_p (), 0, 0);
		  pop_momentary (); }
	;

/* Value is number of statements counted as of the closeparen.  */
simple_if:
	  IF '(' expr ')'
		{ emit_line_note ($<filename>-1, $<lineno>0);
		  expand_start_cond (truthvalue_conversion ($3), 0);
		  $<itype>1 = stmt_count;
		  if_stmt_file = $<filename>-1;
		  if_stmt_line = $<lineno>0;
		  position_after_white_space (); }
	  lineno_stmt
	;

save_filename:
		{ $$ = input_filename; }
	;

save_lineno:
		{ $$ = lineno; }
	;

lineno_stmt:
	  save_filename save_lineno stmt
		{ }
	;

stmt:
	  compstmt
		{ stmt_count++; }
	| expr ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  c_expand_expr_stmt ($1);
		  clear_momentary (); }
	| simple_if ELSE
		{ expand_start_else ();
		  $<itype>1 = stmt_count;
		  position_after_white_space (); }
	  lineno_stmt
		{ expand_end_cond ();
		  if (extra_warnings && stmt_count == $<itype>1)
		    warning ("empty body in an else-statement"); }
	| simple_if %prec IF
		{ expand_end_cond ();
		  if (extra_warnings && stmt_count == $<itype>1)
		    warning_with_file_and_line (if_stmt_file, if_stmt_line,
						"empty body in an if-statement"); }
	| WHILE
		{ emit_nop ();
		  stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  expand_start_loop (1); }
	  '(' expr ')'
		{ emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (0, truthvalue_conversion ($4));
		  position_after_white_space (); }
	  lineno_stmt
		{ expand_end_loop (); }
	| DO
		{ emit_nop ();
		  stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  expand_start_loop_continue_elsewhere (1);
		  position_after_white_space (); }
	  lineno_stmt WHILE
		{ expand_loop_continue_here (); }
	  '(' expr ')' ';'
		{ emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (0, truthvalue_conversion ($7));
		  expand_end_loop ();
		  clear_momentary (); }
	| FOR
	  '(' xexpr ';'
		{ emit_nop ();
		  stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  if ($3) c_expand_expr_stmt ($3);
		  expand_start_loop_continue_elsewhere (1); }
	  xexpr ';'
		{ emit_line_note (input_filename, lineno);
		  if ($6)
		    expand_exit_loop_if_false (0, truthvalue_conversion ($6)); }
	  xexpr ')'
		/* Don't let the tree nodes for $9 be discarded
		   by clear_momentary during the parsing of the next stmt.  */
		{ push_momentary ();
		  position_after_white_space (); }
	  lineno_stmt
		{ emit_line_note ($<filename>-1, $<lineno>0);
		  expand_loop_continue_here ();
		  if ($9)
		    c_expand_expr_stmt ($9);
		  pop_momentary ();
		  expand_end_loop (); }
	| SWITCH '(' expr ')'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  c_expand_start_case ($3);
		  /* Don't let the tree nodes for $3 be discarded by
		     clear_momentary during the parsing of the next stmt.  */
		  push_momentary ();
		  position_after_white_space (); }
	  lineno_stmt
		{ expand_end_case ($3);
		  pop_momentary (); }
	| CASE expr ':'
		{ register tree value = check_case_value ($2);
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);

		  stmt_count++;

		  if (value != error_mark_node)
		    {
		      tree duplicate;
		      int success = pushcase (value, label, &duplicate);
		      if (success == 1)
			error ("case label not within a switch statement");
		      else if (success == 2)
			{
			  error ("duplicate case value");
			  error_with_decl (duplicate, "this is the first entry for that value");
			}
		      else if (success == 3)
			warning ("case value out of range");
		      else if (success == 5)
			error ("case label within scope of cleanup or variable array");
		    }
		  position_after_white_space (); }
	  lineno_stmt
	| CASE expr ELLIPSIS expr ':'
		{ register tree value1 = check_case_value ($2);
		  register tree value2 = check_case_value ($4);
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);

		  stmt_count++;

		  if (value1 != error_mark_node && value2 != error_mark_node)
		    {
		      tree duplicate;
		      int success = pushcase_range (value1, value2, label,
						    &duplicate);
		      if (success == 1)
			error ("case label not within a switch statement");
		      else if (success == 2)
			{
			  error ("duplicate case value");
			  error_with_decl (duplicate, "this is the first entry overlapping that value");
			}
		      else if (success == 3)
			warning ("case value out of range");
		      else if (success == 4)
			warning ("empty case range");
		      else if (success == 5)
			error ("case label within scope of cleanup or variable array");
		    }
		  position_after_white_space (); }
	  lineno_stmt
	| DEFAULT ':'
		{
		  tree duplicate;
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);
		  int success = pushcase (NULL_TREE, label, &duplicate);
		  stmt_count++;
		  if (success == 1)
		    error ("default label not within a switch statement");
		  else if (success == 2)
		    {
		      error ("multiple default labels in one switch");
		      error_with_decl (duplicate, "this is the first default albel");
		    }
		  position_after_white_space (); }
	  lineno_stmt
	| BREAK ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  if ( ! expand_exit_something ())
		    error ("break statement not within loop or switch"); }
	| CONTINUE ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  if (! expand_continue_loop (0))
		    error ("continue statement not within a loop"); }
	| RETURN ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  c_expand_return (NULL_TREE); }
	| RETURN expr ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  c_expand_return ($2); }
	| ASM_KEYWORD maybe_type_qual '(' string ')' ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  if (TREE_CHAIN ($4)) $4 = combine_strings ($4);
		  expand_asm ($4); }
	/* This is the case with just output operands.  */
	| ASM_KEYWORD maybe_type_qual '(' string ':' asm_operands ')' ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  if (TREE_CHAIN ($4)) $4 = combine_strings ($4);
		  c_expand_asm_operands ($4, $6, NULL_TREE, NULL_TREE,
					 $2 == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
	/* This is the case with input operands as well.  */
	| ASM_KEYWORD maybe_type_qual '(' string ':' asm_operands ':' asm_operands ')' ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  if (TREE_CHAIN ($4)) $4 = combine_strings ($4);
		  c_expand_asm_operands ($4, $6, $8, NULL_TREE,
					 $2 == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
	/* This is the case with clobbered registers as well.  */
	| ASM_KEYWORD maybe_type_qual '(' string ':' asm_operands ':'
  	  asm_operands ':' asm_clobbers ')' ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  if (TREE_CHAIN ($4)) $4 = combine_strings ($4);
		  c_expand_asm_operands ($4, $6, $8, $10,
					 $2 == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
	| GOTO identifier ';'
		{ tree decl;
		  stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  decl = lookup_label ($2);
		  if (decl != 0)
		    {
		      TREE_USED (decl) = 1;
		      expand_goto (decl);
		    }
		}
	| GOTO '*' expr ';'
		{ stmt_count++;
		  emit_line_note ($<filename>-1, $<lineno>0);
		  expand_computed_goto ($3); }
	| identifier ':'
		{ tree label = define_label (input_filename, lineno, $1);
		  stmt_count++;
		  emit_nop ();
		  if (label)
		    expand_label (label);
		  position_after_white_space (); }
	  lineno_stmt
	| ';'
	;

/* Either a type-qualifier or nothing.  First thing in an `asm' statement.  */

maybe_type_qual:
	/* empty */
		{ if (pedantic)
		    pedwarn ("ANSI C forbids use of `asm' keyword");
		  emit_line_note (input_filename, lineno); }
	| TYPE_QUAL
		{ if (pedantic)
		    pedwarn ("ANSI C forbids use of `asm' keyword");
		  emit_line_note (input_filename, lineno); }
	;

xexpr:
	/* empty */
		{ $$ = NULL_TREE; }
	| expr
	;

/* These are the operands other than the first string and colon
   in  asm ("addextend %2,%1": "=dm" (x), "0" (y), "g" (*x))  */
asm_operands: /* empty */
		{ $$ = NULL_TREE; }
	| nonnull_asm_operands
	;

nonnull_asm_operands:
	  asm_operand
	| nonnull_asm_operands ',' asm_operand
		{ $$ = chainon ($1, $3); }
	;

asm_operand:
	  STRING '(' expr ')'
		{ $$ = build_tree_list ($1, $3); }
	;

asm_clobbers:
	  string
		{ $$ = tree_cons (NULL_TREE, combine_strings ($1), NULL_TREE); }
	| asm_clobbers ',' string
		{ $$ = tree_cons (NULL_TREE, combine_strings ($3), $1); }
	;

/* This is what appears inside the parens in a function declarator.
   Its value is a list of ..._TYPE nodes.  */
parmlist:
		{ pushlevel (0);
		  declare_parm_level (0); }
	  parmlist_1
		{ $$ = $2;
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
	;

/* This is referred to where either a parmlist or an identifier list is ok.
   Its value is a list of ..._TYPE nodes or a list of identifiers.  */
parmlist_or_identifiers:
		{ pushlevel (0);
		  declare_parm_level (1); }
	  parmlist_or_identifiers_1
		{ $$ = $2;
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
	;

parmlist_or_identifiers_1:
	  parmlist_2 ')'
	| identifiers ')'
		{ $$ = tree_cons (NULL_TREE, NULL_TREE, $1); }
	| error ')'
		{ $$ = tree_cons (NULL_TREE, NULL_TREE, NULL_TREE); }
	;

parmlist_1:
	  parmlist_2 ')'
	| error ')'
		{ $$ = tree_cons (NULL_TREE, NULL_TREE, NULL_TREE); }
	;

/* This is what appears inside the parens in a function declarator.
   Is value is represented in the format that grokdeclarator expects.  */
parmlist_2:  /* empty */
		{ $$ = get_parm_info (0); }
	| parms
		{ $$ = get_parm_info (1); }
	| parms ',' ELLIPSIS
		{ $$ = get_parm_info (0); }
	;

parms:
	parm
		{ push_parm_decl ($1); }
	| parms ',' parm
		{ push_parm_decl ($3); }
	;

/* A single parameter declaration or parameter type name,
   as found in a parmlist.  */
parm:
	  typed_declspecs parm_declarator
		{ $$ = build_tree_list ($1, $2)	; }
	| typed_declspecs notype_declarator
		{ $$ = build_tree_list ($1, $2)	; }
	| typed_declspecs absdcl
		{ $$ = build_tree_list ($1, $2); }
	| declmods notype_declarator
		{ $$ = build_tree_list ($1, $2)	; }
	| declmods absdcl
		{ $$ = build_tree_list ($1, $2); }
	;

/* A nonempty list of identifiers.  */
identifiers:
	IDENTIFIER
		{ $$ = build_tree_list (NULL_TREE, $1); }
	| identifiers ',' IDENTIFIER
		{ $$ = chainon ($1, build_tree_list (NULL_TREE, $3)); }
	;

/*
 *	Objective-C productions.
 */
objcdef:
	  classdef
	| methoddef
	| END
		{
		  if (objc_implementation_context)
                    {
		      finish_class (objc_implementation_context);
		      objc_ivar_chain = NULL_TREE;
		      objc_implementation_context = NULL_TREE;
		    }
		  else
		    warning ("`@end' must appear in an implementation context");
		}
	;

classdef:
	  INTERFACE identifier '{'
		{
		  objc_interface_context = objc_ivar_context
		    = start_class (INTERFACE_TYPE, $2, NULL_TREE);
                  objc_public_flag = 0;
		}
	  ivar_decl_list '}'
		{
                  continue_class (objc_interface_context);
		}
	  methodprotolist
	  END
		{
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}

	| INTERFACE identifier
		{
		  objc_interface_context
		    = start_class (INTERFACE_TYPE, $2, NULL_TREE);
                  continue_class (objc_interface_context);
		}
	  methodprotolist
	  END
		{
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}

	| INTERFACE identifier ':' identifier '{'
		{
		  objc_interface_context = objc_ivar_context
		    = start_class (INTERFACE_TYPE, $2, $4);
                  objc_public_flag = 0;
		}
	  ivar_decl_list '}'
		{
                  continue_class (objc_interface_context);
		}
	  methodprotolist
	  END
		{
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}

	| INTERFACE identifier ':' identifier
		{
		  objc_interface_context
		    = start_class (INTERFACE_TYPE, $2, $4);
                  continue_class (objc_interface_context);
		}
	  methodprotolist
	  END
		{
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}

	| IMPLEMENTATION identifier '{'
		{
		  objc_implementation_context = objc_ivar_context
		    = start_class (IMPLEMENTATION_TYPE, $2, NULL_TREE);
                  objc_public_flag = 0;
		}
	  ivar_decl_list '}'
		{
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}

	| IMPLEMENTATION identifier
		{
		  objc_implementation_context
		    = start_class (IMPLEMENTATION_TYPE, $2, NULL_TREE);
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}

	| IMPLEMENTATION identifier ':' identifier '{'
		{
		  objc_implementation_context = objc_ivar_context
		    = start_class (IMPLEMENTATION_TYPE, $2, $4);
                  objc_public_flag = 0;
		}
	  ivar_decl_list '}'
		{
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}

	| IMPLEMENTATION identifier ':' identifier
		{
		  objc_implementation_context
		    = start_class (IMPLEMENTATION_TYPE, $2, $4);
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}

	| INTERFACE identifier '(' identifier ')'
		{
		  objc_interface_context
		    = start_class (PROTOCOL_TYPE, $2, $4);
                  continue_class (objc_interface_context);
		}
	  methodprotolist
	  END
		{
		  finish_class (objc_interface_context);
		  objc_interface_context = NULL_TREE;
		}

	| IMPLEMENTATION identifier '(' identifier ')'
		{
		  objc_implementation_context
		    = start_class (CATEGORY_TYPE, $2, $4);
                  objc_ivar_chain
		    = continue_class (objc_implementation_context);
		}
	;

ivar_decl_list:
          ivar_decls PUBLIC { objc_public_flag = 1; } ivar_decls
        | ivar_decls
        ;

ivar_decls:
          /* empty */
		{
                  $$ = NULL_TREE;
                }
	| ivar_decls ivar_decl ';'
	| ivar_decls ';'
		{
                  if (pedantic)
		    warning ("extra semicolon in struct or union specified");
                }
	;


/* There is a shift-reduce conflict here, because `components' may
   start with a `typename'.  It happens that shifting (the default resolution)
   does the right thing, because it treats the `typename' as part of
   a `typed_typespecs'.

   It is possible that this same technique would allow the distinction
   between `notype_initdecls' and `initdecls' to be eliminated.
   But I am being cautious and not trying it.  */

ivar_decl:
	typed_typespecs setspecs ivars
	        {
                  $$ = $3;
		  resume_momentary ($2);
                }
	| nonempty_type_quals setspecs ivars
		{
                  $$ = $3;
		  resume_momentary ($2);
                }
	| error
		{ $$ = NULL_TREE; }
	;

ivars:
	  /* empty */
		{ $$ = NULL_TREE; }
	| ivar_declarator
	| ivars ',' ivar_declarator
	;

ivar_declarator:
	  declarator
		{
		  $$ = add_instance_variable (objc_ivar_context,
					      objc_public_flag,
					      $1, current_declspecs,
					      NULL_TREE);
                }
	| declarator ':' expr_no_commas
		{
		  $$ = add_instance_variable (objc_ivar_context,
					      objc_public_flag,
					      $1, current_declspecs, $3);
                }
	| ':' expr_no_commas
		{
		  $$ = add_instance_variable (objc_ivar_context,
					      objc_public_flag,
					      NULL_TREE,
					      current_declspecs, $2);
                }
	;

methoddef:
	  '+'
		{
		  if (objc_implementation_context)
		    objc_inherit_code = CLASS_METHOD_DECL;
                  else
		    fatal ("method definition not in class context");
		}
	  methoddecl
		{
		  add_class_method (objc_implementation_context, $3);
		  start_method_def ($3);
		  objc_method_context = $3;
		}
	  optarglist
		{
		  continue_method_def ();
		}
	  compstmt_or_error
		{
		  finish_method_def ();
		  objc_method_context = NULL_TREE;
		}

	| '-'
		{
		  if (objc_implementation_context)
		    objc_inherit_code = INSTANCE_METHOD_DECL;
                  else
		    fatal ("method definition not in class context");
		}
	  methoddecl
		{
		  add_instance_method (objc_implementation_context, $3);
		  start_method_def ($3);
		  objc_method_context = $3;
		}
	  optarglist
		{
		  continue_method_def ();
		}
	  compstmt_or_error
		{
		  finish_method_def ();
		  objc_method_context = NULL_TREE;
		}
	;

/* the reason for the strange actions in this rule
 is so that notype_initdecls when reached via datadef
 can find a valid list of type and sc specs in $0. */

methodprotolist:
	  /* empty  */
	| {$<ttype>$ = NULL_TREE; } methodprotolist2
	;

methodprotolist2:		 /* eliminates a shift/reduce conflict */
	   methodproto
	|  datadef
	| methodprotolist2 methodproto
	| methodprotolist2 {$<ttype>$ = NULL_TREE; } datadef
	;

semi_or_error:
	  ';'
	| error
	;

methodproto:
	  '+'
		{
		  objc_inherit_code = CLASS_METHOD_DECL;
		}
	  methoddecl
		{
		  add_class_method (objc_interface_context, $3);
		}
	  semi_or_error

	| '-'
		{
		  objc_inherit_code = INSTANCE_METHOD_DECL;
		}
	  methoddecl
		{
		  add_instance_method (objc_interface_context, $3);
		}
	  semi_or_error
	;

methoddecl:
	  '(' typename ')' unaryselector
		{
		  $$ = build_method_decl (objc_inherit_code, $2, $4, NULL_TREE);
		}

	| unaryselector
		{
		  $$ = build_method_decl (objc_inherit_code, NULL_TREE, $1, NULL_TREE);
		}

	| '(' typename ')' keywordselector optparmlist
		{
		  $$ = build_method_decl (objc_inherit_code, $2, $4, $5);
		}

	| keywordselector optparmlist
		{
		  $$ = build_method_decl (objc_inherit_code, NULL_TREE, $1, $2);
		}
	;

/* "optarglist" assumes that start_method_def has already been called...
   if it is not, the "xdecls" will not be placed in the proper scope */

optarglist:
	  /* empty */
	| ';' myxdecls
	;

/* to get around the following situation: "int foo (int a) int b; {}" that
   is synthesized when parsing "- a:a b:b; id c; id d; { ... }" */

myxdecls:
	  /* empty */
	| mydecls
	;

mydecls:
	mydecl
	| errstmt
	| mydecls mydecl
	| mydecl errstmt
	;

mydecl:
	typed_declspecs setspecs myparms ';'
		{ resume_momentary ($2); }
	| typed_declspecs ';'
		{ shadow_tag ($1); }
	| declmods ';'
		{ warning ("empty declaration"); }
	;

myparms:
	myparm
		{ push_parm_decl ($1); }
	| myparms ',' myparm
		{ push_parm_decl ($3); }
	;

/* A single parameter declaration or parameter type name,
   as found in a parmlist. DOES NOT ALLOW AN INITIALIZER OR ASMSPEC */

myparm:
	  parm_declarator
		{ $$ = build_tree_list (current_declspecs, $1)	; }
	| notype_declarator
		{ $$ = build_tree_list (current_declspecs, $1)	; }
	| absdcl
		{ $$ = build_tree_list (current_declspecs, $1)	; }
	;

optparmlist:
	  /* empty */
		{
	    	  $$ = NULL_TREE;
		}
	| ',' ELLIPSIS
		{
		  /* oh what a kludge! */
		  $$ = (tree)1;
		}
	| ','
		{
		  pushlevel (0);
		}
	  parmlist_2
		{
	  	  /* returns a tree list node generated by get_parm_info */
		  $$ = $3;
		  poplevel (0, 0, 0);
		}
	;

unaryselector:
	  selector
	;

keywordselector:
	  keyworddecl

	| keywordselector keyworddecl
		{
		  $$ = chainon ($1, $2);
		}
	;

selector:
	  IDENTIFIER
        | TYPENAME
	| reservedwords
	;

reservedwords:
	  ENUM { $$ = get_identifier (token_buffer); }
	| STRUCT { $$ = get_identifier (token_buffer); }
	| UNION { $$ = get_identifier (token_buffer); }
	| IF { $$ = get_identifier (token_buffer); }
	| ELSE { $$ = get_identifier (token_buffer); }
	| WHILE { $$ = get_identifier (token_buffer); }
	| DO { $$ = get_identifier (token_buffer); }
	| FOR { $$ = get_identifier (token_buffer); }
	| SWITCH { $$ = get_identifier (token_buffer); }
	| CASE { $$ = get_identifier (token_buffer); }
	| DEFAULT { $$ = get_identifier (token_buffer); }
	| BREAK { $$ = get_identifier (token_buffer); }
	| CONTINUE { $$ = get_identifier (token_buffer); }
	| RETURN  { $$ = get_identifier (token_buffer); }
	| GOTO { $$ = get_identifier (token_buffer); }
	| ASM_KEYWORD { $$ = get_identifier (token_buffer); }
        | SIZEOF { $$ = get_identifier (token_buffer); }
	| TYPEOF { $$ = get_identifier (token_buffer); }
	| ALIGNOF { $$ = get_identifier (token_buffer); }
	| TYPESPEC | TYPE_QUAL
	;

keyworddecl:
	  selector ':' '(' typename ')' identifier
		{
		  $$ = build_keyword_decl ($1, $4, $6);
		}

	| selector ':' identifier
		{
		  $$ = build_keyword_decl ($1, NULL_TREE, $3);
		}

	| ':' '(' typename ')' identifier
		{
		  $$ = build_keyword_decl (NULL_TREE, $3, $5);
		}

	| ':' identifier
		{
		  $$ = build_keyword_decl (NULL_TREE, NULL_TREE, $2);
		}
	;

messageargs:
	  selector
        | keywordarglist
	;

keywordarglist:
	  keywordarg
	| keywordarglist keywordarg
		{
		  $$ = chainon ($1, $2);
		}
	;


keywordexpr:
	  nonnull_exprlist
		{
		  if (TREE_CHAIN ($1) == NULL_TREE)
		    /* just return the expr., remove a level of indirection */
		    $$ = TREE_VALUE ($1);
                  else
		    /* we have a comma expr., we will collapse later */
		    $$ = $1;
		}
	;

keywordarg:
	  selector ':' keywordexpr
		{
		  $$ = build_tree_list ($1, $3);
		}
	| ':' keywordexpr
		{
		  $$ = build_tree_list (NULL_TREE, $2);
		}
	;

receiver:
	  expr
	| CLASSNAME
		{
		  $$ = get_class_reference ($1);
		}
	;

objcmessageexpr:
	  '['
		{ objc_receiver_context = 1; }
	  receiver
		{ objc_receiver_context = 0; }
	  messageargs ']'
		{
		  $$ = build_tree_list ($3, $5);
		}
	;

selectorarg:
	  selector
        | keywordnamelist
	;

keywordnamelist:
	  keywordname
	| keywordnamelist keywordname
		{
		  $$ = chainon ($1, $2);
		}
	;

keywordname:
	  selector ':'
		{
		  $$ = build_tree_list ($1, NULL_TREE);
		}
	| ':'
		{
		  $$ = build_tree_list (NULL_TREE, NULL_TREE);
		}
	;

objcselectorexpr:
	  SELECTOR '(' selectorarg ')'
		{
		  $$ = $3;
		}
	;

/* extension to support C-structures in the archiver */

objcencodeexpr:
	  ENCODE '(' typename ')'
		{
		  $$ = groktypename ($3);
		}
	;
%%
/* If STRING is the name of an Objective C @-keyword
   (not including the @), return the token type for that keyword.
   Otherwise return 0.  */

int
recognize_objc_keyword (string)
     char *string;
{
  switch (string[0])
    {
    case 'd':
      if (!strcmp (string, "defs"))
	return DEFS;
      break;
    case 'e':
      if (!strcmp (string, "end"))
	return END;
      if (!strcmp (string, "encode"))
	return ENCODE;
      break;
    case 'i':
      if (!strcmp (string, "interface"))
	return INTERFACE;
      if (!strcmp (string, "implementation"))
	return IMPLEMENTATION;
      break;
    case 'p':
      if (!strcmp (string, "public"))
	return PUBLIC;
      break;
    case 's':
      if (!strcmp (string, "selector"))
	return SELECTOR;
      break;
    }
  return 0;
}
