/* explow.c -- changed for emx by Eberhard Mattes -- Mar 1992 */

/* Subroutines for manipulating rtx's in semantically interesting ways.
   Copyright (C) 1987, 1991 Free Software Foundation, Inc.

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


#include "config.h"
#include "rtl.h"
#include "tree.h"
#include "flags.h"
#include "expr.h"
#include "hard-reg-set.h"
#include "insn-config.h"
#include "recog.h"
#include "insn-flags.h"
#include "insn-codes.h"

/* Return an rtx for the sum of X and the integer C.  */

rtx
plus_constant (x, c)
     register rtx x;
     register int c;
{
  register RTX_CODE code;
  register enum machine_mode mode;
  register rtx tem;
  int all_constant = 0;

  if (c == 0)
    return x;

 restart:

  code = GET_CODE (x);
  mode = GET_MODE (x);
  switch (code)
    {
    case CONST_INT:
      return gen_rtx (CONST_INT, VOIDmode, (INTVAL (x) + c));

    case CONST_DOUBLE:
      {
	int l1 = CONST_DOUBLE_LOW (x);
	int h1 = CONST_DOUBLE_HIGH (x);
	int l2 = c;
	int h2 = c < 0 ? ~0 : 0;
	int lv, hv;

	add_double (l1, h1, l2, h2, &lv, &hv);

	return immed_double_const (lv, hv, VOIDmode);
      }

    case MEM:
      /* If this is a reference to the constant pool, try replacing it with
	 a reference to a new constant.  If the resulting address isn't
	 valid, don't return it because we have no way to validize it.  */
      if (GET_CODE (XEXP (x, 0)) == SYMBOL_REF
	  && CONSTANT_POOL_ADDRESS_P (XEXP (x, 0)))
	{
	  tem
	    = force_const_mem (GET_MODE (x),
			       plus_constant (get_pool_constant (XEXP (x, 0)),
					      c));
	  if (memory_address_p (GET_MODE (tem), XEXP (tem, 0)))
	    return tem;
	}
      break;

    case CONST:
      /* If adding to something entirely constant, set a flag
	 so that we can add a CONST around the result.  */
      x = XEXP (x, 0);
      all_constant = 1;
      goto restart;

    case SYMBOL_REF:
    case LABEL_REF:
      all_constant = 1;
      break;

    case PLUS:
      /* The interesting case is adding the integer to a sum.
	 Look for constant term in the sum and combine
	 with C.  For an integer constant term, we make a combined
	 integer.  For a constant term that is not an explicit integer,
	 we cannot really combine, but group them together anyway.  */
      if (GET_CODE (XEXP (x, 0)) == CONST_INT)
	{
	  c += INTVAL (XEXP (x, 0));
	  x = XEXP (x, 1);
	}
      else if (GET_CODE (XEXP (x, 1)) == CONST_INT)
	{
	  c += INTVAL (XEXP (x, 1));
	  x = XEXP (x, 0);
	}
      else if (CONSTANT_P (XEXP (x, 0)))
	return gen_rtx (PLUS, mode,
			plus_constant (XEXP (x, 0), c),
			XEXP (x, 1));
      else if (CONSTANT_P (XEXP (x, 1)))
	return gen_rtx (PLUS, mode,
			XEXP (x, 0),
			plus_constant (XEXP (x, 1), c));
    }

  if (c != 0)
    x = gen_rtx (PLUS, mode, x, gen_rtx (CONST_INT, VOIDmode, c));

  if (GET_CODE (x) == SYMBOL_REF || GET_CODE (x) == LABEL_REF)
    return x;
  else if (all_constant)
    return gen_rtx (CONST, mode, x);
  else
    return x;
}

/* This is the same a `plus_constant', except that it handles LO_SUM.  */

rtx
plus_constant_for_output (x, c)
     register rtx x;
     register int c;
{
  register RTX_CODE code = GET_CODE (x);
  register enum machine_mode mode = GET_MODE (x);
  int all_constant = 0;

  if (GET_CODE (x) == LO_SUM)
    return gen_rtx (LO_SUM, mode, XEXP (x, 0),
		    plus_constant_for_output (XEXP (x, 1), c));

  else
    return plus_constant (x, c);
}

/* If X is a sum, return a new sum like X but lacking any constant terms.
   Add all the removed constant terms into *CONSTPTR.
   X itself is not altered.  The result != X if and only if
   it is not isomorphic to X.  */

rtx
eliminate_constant_term (x, constptr)
     rtx x;
     rtx *constptr;
{
  register rtx x0, x1;
  rtx tem;

  if (GET_CODE (x) != PLUS)
    return x;

  /* First handle constants appearing at this level explicitly.  */
  if (GET_CODE (XEXP (x, 1)) == CONST_INT
      && 0 != (tem = simplify_binary_operation (PLUS, GET_MODE (x), *constptr,
						XEXP (x, 1)))
      && GET_CODE (tem) == CONST_INT)
    {
      *constptr = tem;
      return eliminate_constant_term (XEXP (x, 0), constptr);
    }

  tem = const0_rtx;
  x0 = eliminate_constant_term (XEXP (x, 0), &tem);
  x1 = eliminate_constant_term (XEXP (x, 1), &tem);
  if ((x1 != XEXP (x, 1) || x0 != XEXP (x, 0))
      && 0 != (tem = simplify_binary_operation (PLUS, GET_MODE (x),
						*constptr, tem))
      && GET_CODE (tem) == CONST_INT)
    {
      *constptr = tem;
      return gen_rtx (PLUS, GET_MODE (x), x0, x1);
    }

  return x;
}

/* Returns the insn that next references REG after INSN, or 0
   if REG is clobbered before next referenced or we cannot find
   an insn that references REG in a straight-line piece of code.  */

rtx
find_next_ref (reg, insn)
     rtx reg;
     rtx insn;
{
  rtx next;

  for (insn = NEXT_INSN (insn); insn; insn = next)
    {
      next = NEXT_INSN (insn);
      if (GET_CODE (insn) == NOTE)
	continue;
      if (GET_CODE (insn) == CODE_LABEL
	  || GET_CODE (insn) == BARRIER)
	return 0;
      if (GET_CODE (insn) == INSN
	  || GET_CODE (insn) == JUMP_INSN
	  || GET_CODE (insn) == CALL_INSN)
	{
	  if (reg_set_p (reg, insn))
	    return 0;
	  if (reg_mentioned_p (reg, PATTERN (insn)))
	    return insn;
	  if (GET_CODE (insn) == JUMP_INSN)
	    {
	      if (simplejump_p (insn))
		next = JUMP_LABEL (insn);
	      else
		return 0;
	    }
	  if (GET_CODE (insn) == CALL_INSN
	      && REGNO (reg) < FIRST_PSEUDO_REGISTER
	      && call_used_regs[REGNO (reg)])
	    return 0;
	}
      else
	abort ();
    }
  return 0;
}

/* Return an rtx for the size in bytes of the value of EXP.  */

rtx
expr_size (exp)
     tree exp;
{
  return expand_expr (size_in_bytes (TREE_TYPE (exp)),
		      0, TYPE_MODE (sizetype), 0);
}

/* Return a copy of X in which all memory references
   and all constants that involve symbol refs
   have been replaced with new temporary registers.
   Also emit code to load the memory locations and constants
   into those registers.

   If X contains no such constants or memory references,
   X itself (not a copy) is returned.

   If a constant is found in the address that is not a legitimate constant
   in an insn, it is left alone in the hope that it might be valid in the
   address.

   X may contain no arithmetic except addition, subtraction and multiplication.
   Values returned by expand_expr with 1 for sum_ok fit this constraint.  */

static rtx
break_out_memory_refs (x)
     register rtx x;
{
  if (GET_CODE (x) == MEM
      || (CONSTANT_P (x) && LEGITIMATE_CONSTANT_P (x)
	  && GET_MODE (x) != VOIDmode))
    {
      register rtx temp = force_reg (GET_MODE (x), x);
      mark_reg_pointer (temp);
      x = temp;
    }
  else if (GET_CODE (x) == PLUS || GET_CODE (x) == MINUS
	   || GET_CODE (x) == MULT)
    {
      register rtx op0 = break_out_memory_refs (XEXP (x, 0));
      register rtx op1 = break_out_memory_refs (XEXP (x, 1));
      if (op0 != XEXP (x, 0) || op1 != XEXP (x, 1))
	x = gen_rtx (GET_CODE (x), Pmode, op0, op1);
    }
  return x;
}

/* Given a memory address or facsimile X, construct a new address,
   currently equivalent, that is stable: future stores won't change it.

   X must be composed of constants, register and memory references
   combined with addition, subtraction and multiplication:
   in other words, just what you can get from expand_expr if sum_ok is 1.

   Works by making copies of all regs and memory locations used
   by X and combining them the same way X does.
   You could also stabilize the reference to this address
   by copying the address to a register with copy_to_reg;
   but then you wouldn't get indexed addressing in the reference.  */

rtx
copy_all_regs (x)
     register rtx x;
{
  if (GET_CODE (x) == REG)
    {
      if (REGNO (x) != FRAME_POINTER_REGNUM)
	x = copy_to_reg (x);
    }
  else if (GET_CODE (x) == MEM)
    x = copy_to_reg (x);
  else if (GET_CODE (x) == PLUS || GET_CODE (x) == MINUS
	   || GET_CODE (x) == MULT)
    {
      register rtx op0 = copy_all_regs (XEXP (x, 0));
      register rtx op1 = copy_all_regs (XEXP (x, 1));
      if (op0 != XEXP (x, 0) || op1 != XEXP (x, 1))
	x = gen_rtx (GET_CODE (x), Pmode, op0, op1);
    }
  return x;
}

/* Return something equivalent to X but valid as a memory address
   for something of mode MODE.  When X is not itself valid, this
   works by copying X or subexpressions of it into registers.  */

rtx
memory_address (mode, x)
     enum machine_mode mode;
     register rtx x;
{
  register rtx oldx;

  /* By passing constant addresses thru registers
     we get a chance to cse them.  */
  if (! cse_not_expected && CONSTANT_P (x) && LEGITIMATE_CONSTANT_P (x))
    return force_reg (Pmode, x);

  /* Accept a QUEUED that refers to a REG
     even though that isn't a valid address.
     On attempting to put this in an insn we will call protect_from_queue
     which will turn it into a REG, which is valid.  */
  if (GET_CODE (x) == QUEUED
      && GET_CODE (QUEUED_VAR (x)) == REG)
    return x;

  /* We get better cse by rejecting indirect addressing at this stage.
     Let the combiner create indirect addresses where appropriate.
     For now, generate the code so that the subexpressions useful to share
     are visible.  But not if cse won't be done!  */
  oldx = x;
  if (! cse_not_expected && GET_CODE (x) != REG)
    x = break_out_memory_refs (x);

  /* At this point, any valid address is accepted.  */
  GO_IF_LEGITIMATE_ADDRESS (mode, x, win);

  /* If it was valid before but breaking out memory refs invalidated it,
     use it the old way.  */
  if (memory_address_p (mode, oldx))
    goto win2;

  /* Perform machine-dependent transformations on X
     in certain cases.  This is not necessary since the code
     below can handle all possible cases, but machine-dependent
     transformations can make better code.  */
  LEGITIMIZE_ADDRESS (x, oldx, mode, win);

  /* PLUS and MULT can appear in special ways
     as the result of attempts to make an address usable for indexing.
     Usually they are dealt with by calling force_operand, below.
     But a sum containing constant terms is special
     if removing them makes the sum a valid address:
     then we generate that address in a register
     and index off of it.  We do this because it often makes
     shorter code, and because the addresses thus generated
     in registers often become common subexpressions.  */
  if (GET_CODE (x) == PLUS)
    {
      rtx constant_term = const0_rtx;
      rtx y = eliminate_constant_term (x, &constant_term);
      if (constant_term == const0_rtx
	  || ! memory_address_p (mode, y))
	return force_operand (x, 0);

      y = gen_rtx (PLUS, GET_MODE (x), copy_to_reg (y), constant_term);
      if (! memory_address_p (mode, y))
	return force_operand (x, 0);
      return y;
    }
  if (GET_CODE (x) == MULT || GET_CODE (x) == MINUS)
    return force_operand (x, 0);

  /* If we have a register that's an invalid address,
     it must be a hard reg of the wrong class.  Copy it to a pseudo.  */
  if (GET_CODE (x) == REG)
    return copy_to_reg (x);

  /* Last resort: copy the value to a register, since
     the register is a valid address.  */
  return force_reg (Pmode, x);

 win2:
  x = oldx;
 win:
  if (flag_force_addr && ! cse_not_expected && GET_CODE (x) != REG
      /* Don't copy an addr via a reg if it is one of our stack slots.  */
      && ! (GET_CODE (x) == PLUS
	    && (XEXP (x, 0) == virtual_stack_vars_rtx
		|| XEXP (x, 0) == virtual_incoming_args_rtx)))
    {
      if (general_operand (x, Pmode))
	return force_reg (Pmode, x);
      else
	return force_operand (x, 0);
    }
  return x;
}

/* Like `memory_address' but pretend `flag_force_addr' is 0.  */

rtx
memory_address_noforce (mode, x)
     enum machine_mode mode;
     rtx x;
{
  int ambient_force_addr = flag_force_addr;
  rtx val;

  flag_force_addr = 0;
  val = memory_address (mode, x);
  flag_force_addr = ambient_force_addr;
  return val;
}

/* Convert a mem ref into one with a valid memory address.
   Pass through anything else unchanged.  */

rtx
validize_mem (ref)
     rtx ref;
{
  if (GET_CODE (ref) != MEM)
    return ref;
  if (memory_address_p (GET_MODE (ref), XEXP (ref, 0)))
    return ref;
  /* Don't alter REF itself, since that is probably a stack slot.  */
  return change_address (ref, GET_MODE (ref), XEXP (ref, 0));
}

/* Return a modified copy of X with its memory address copied
   into a temporary register to protect it from side effects.
   If X is not a MEM, it is returned unchanged (and not copied).
   Perhaps even if it is a MEM, if there is no need to change it.  */

rtx
stabilize (x)
     rtx x;
{
  register rtx addr;
  if (GET_CODE (x) != MEM)
    return x;
  addr = XEXP (x, 0);
  if (rtx_unstable_p (addr))
    {
      rtx temp = copy_all_regs (addr);
      rtx mem;
      if (GET_CODE (temp) != REG)
	temp = copy_to_reg (temp);
      mem = gen_rtx (MEM, GET_MODE (x), temp);

      /* Mark returned memref with in_struct if it's in an array or
	 structure.  Copy const and volatile from original memref.  */

      MEM_IN_STRUCT_P (mem) = MEM_IN_STRUCT_P (x) || GET_CODE (addr) == PLUS;
      RTX_UNCHANGING_P (mem) = RTX_UNCHANGING_P (x);
      MEM_VOLATILE_P (mem) = MEM_VOLATILE_P (x);
      return mem;
    }
  return x;
}

/* Copy the value or contents of X to a new temp reg and return that reg.  */

rtx
copy_to_reg (x)
     rtx x;
{
  register rtx temp = gen_reg_rtx (GET_MODE (x));
 
  /* If not an operand, must be an address with PLUS and MULT so
     do the computation.  */ 
  if (! general_operand (x, VOIDmode))
    x = force_operand (x, temp);
  
  if (x != temp)
    emit_move_insn (temp, x);

  return temp;
}

/* Like copy_to_reg but always give the new register mode Pmode
   in case X is a constant.  */

rtx
copy_addr_to_reg (x)
     rtx x;
{
  return copy_to_mode_reg (Pmode, x);
}

/* Like copy_to_reg but always give the new register mode MODE
   in case X is a constant.  */

rtx
copy_to_mode_reg (mode, x)
     enum machine_mode mode;
     rtx x;
{
  register rtx temp = gen_reg_rtx (mode);
  
  /* If not an operand, must be an address with PLUS and MULT so
     do the computation.  */ 
  if (! general_operand (x, VOIDmode))
    x = force_operand (x, temp);

  if (GET_MODE (x) != mode && GET_MODE (x) != VOIDmode)
    abort ();
  if (x != temp)
    emit_move_insn (temp, x);
  return temp;
}

/* Load X into a register if it is not already one.
   Use mode MODE for the register.
   X should be valid for mode MODE, but it may be a constant which
   is valid for all integer modes; that's why caller must specify MODE.

   The caller must not alter the value in the register we return,
   since we mark it as a "constant" register.  */

rtx
force_reg (mode, x)
     enum machine_mode mode;
     rtx x;
{
  register rtx temp, insn;

  if (GET_CODE (x) == REG)
    return x;
  temp = gen_reg_rtx (mode);
  insn = emit_move_insn (temp, x);
  /* Let optimizers know that TEMP's value never changes
     and that X can be substituted for it.  */
  if (CONSTANT_P (x))
    {
      rtx note = find_reg_note (insn, REG_EQUAL, 0);

      if (note)
	XEXP (note, 0) = x;
      else
	REG_NOTES (insn) = gen_rtx (EXPR_LIST, REG_EQUAL, x, REG_NOTES (insn));
    }
  return temp;
}

/* If X is a memory ref, copy its contents to a new temp reg and return
   that reg.  Otherwise, return X.  */

rtx
force_not_mem (x)
     rtx x;
{
  register rtx temp;
  if (GET_CODE (x) != MEM || GET_MODE (x) == BLKmode)
    return x;
  temp = gen_reg_rtx (GET_MODE (x));
  emit_move_insn (temp, x);
  return temp;
}

/* Copy X to TARGET (if it's nonzero and a reg)
   or to a new temp reg and return that reg.
   MODE is the mode to use for X in case it is a constant.  */

rtx
copy_to_suggested_reg (x, target, mode)
     rtx x, target;
     enum machine_mode mode;
{
  register rtx temp;

  if (target && GET_CODE (target) == REG)
    temp = target;
  else
    temp = gen_reg_rtx (mode);

  emit_move_insn (temp, x);
  return temp;
}

/* Adjust the stack pointer by ADJUST (an rtx for a number of bytes).
   This pops when ADJUST is positive.  ADJUST need not be constant.  */

void
adjust_stack (adjust)
     rtx adjust;
{
  rtx temp;
  adjust = protect_from_queue (adjust, 0);

  if (adjust == const0_rtx)
    return;

  temp = expand_binop (Pmode,
#ifdef STACK_GROWS_DOWNWARD
		       add_optab,
#else
		       sub_optab,
#endif
		       stack_pointer_rtx, adjust, stack_pointer_rtx, 0,
		       OPTAB_LIB_WIDEN);

  if (temp != stack_pointer_rtx)
    emit_move_insn (stack_pointer_rtx, temp);
}

/* Adjust the stack pointer by minus ADJUST (an rtx for a number of bytes).
   This pushes when ADJUST is positive.  ADJUST need not be constant.  */

void
anti_adjust_stack (adjust)
     rtx adjust;
{
  rtx temp;
  adjust = protect_from_queue (adjust, 0);

  if (adjust == const0_rtx)
    return;

#ifdef __EMX__
  if (TARGET_PROBE &&
          (GET_CODE (adjust) != CONST_INT || INTVAL (adjust) >= PROBE_SIZE))
    {
      int i, j;

      if (GET_CODE (adjust) == CONST_INT && INTVAL (adjust) <= PROBE_MAX_INLINE)
        {
          i = INTVAL (adjust); j = 0;
          while (i >= PROBE_SIZE)
            {
              i -= PROBE_SIZE; j += PROBE_SIZE;
/* (set (mem:QI (plus:SI (reg:SI 7) (const_int -j)) (const_int 0))) */
              emit_insn (gen_rtx (SET, VOIDmode,
                           gen_rtx (MEM, QImode,
                             gen_rtx (PLUS, Pmode,
                               gen_rtx (REG, Pmode, 7), /* esp */
                               gen_rtx (CONST_INT, SImode, -j))),
                           const0_rtx));
            }
        }
      else
        {
          emit_push_insn (adjust, SImode, 0, 0, 0, 0, 0, 0, 0, 0);
/* (call (mem:QI (symbol_ref:SI ("__probe"))) (const_int 1)) */
          emit_insn (gen_rtx (CALL, VOIDmode,
                       gen_rtx (MEM, QImode,
                         gen_rtx (SYMBOL_REF, Pmode, "__probe")),
                       const1_rtx));
          /*
          emit_insn (gen_rtx (ASM_INPUT, VOIDmode, "call ___probe"));
          */
        }
    }
#endif
  temp = expand_binop (Pmode,
#ifdef STACK_GROWS_DOWNWARD
		       sub_optab,
#else
		       add_optab,
#endif
		       stack_pointer_rtx, adjust, stack_pointer_rtx, 0,
		       OPTAB_LIB_WIDEN);

  if (temp != stack_pointer_rtx)
    emit_move_insn (stack_pointer_rtx, temp);
}

/* Round the size of a block to be pushed up to the boundary required
   by this machine.  SIZE is the desired size, which need not be constant.  */

rtx
round_push (size)
     rtx size;
{
#ifdef STACK_BOUNDARY
  int align = STACK_BOUNDARY / BITS_PER_UNIT;
  if (align == 1)
    return size;
  if (GET_CODE (size) == CONST_INT)
    {
      int new = (INTVAL (size) + align - 1) / align * align;
      if (INTVAL (size) != new)
	size = gen_rtx (CONST_INT, VOIDmode, new);
    }
  else
    {
      size = expand_divmod (0, CEIL_DIV_EXPR, Pmode, size,
			    gen_rtx (CONST_INT, VOIDmode, align),
			    0, 1);
      size = expand_mult (Pmode, size,
			  gen_rtx (CONST_INT, VOIDmode, align),
			  0, 1);
    }
#endif /* STACK_BOUNDARY */
  return size;
}

/* Return an rtx representing the address of an area of memory dynamically
   pushed on the stack.  This region of memory is always aligned to
   a multiple of BIGGEST_ALIGNMENT.

   Any required stack pointer alignment is preserved.

   SIZE is an rtx representing the size of the area.
   TARGET is a place in which the address can be placed.  */

rtx
allocate_dynamic_stack_space (size, target)
     rtx size;
     rtx target;
{
  /* Ensure the size is in the proper mode.  */
  if (GET_MODE (size) != VOIDmode && GET_MODE (size) != Pmode)
    size = convert_to_mode (Pmode, size, 1);

  /* We will need to ensure that the address we return is aligned to
     BIGGEST_ALIGNMENT.  If STACK_DYNAMIC_OFFSET is defined, we don't
     always know its final value at this point in the compilation (it 
     might depend on the size of the outgoing parameter lists, for
     example), so we must align the value to be returned in that case.
     (Note that STACK_DYNAMIC_OFFSET will have a default non-zero value if
     STACK_POINTER_OFFSET or ACCUMULATE_OUTGOING_ARGS are defined).
     We must also do an alignment operation on the returned value if
     the stack pointer alignment is less strict that BIGGEST_ALIGNMENT.

     If we have to align, we must leave space in SIZE for the hole
     that might result from the alignment operation.  */

#if defined (STACK_DYNAMIC_OFFSET) || defined(STACK_POINTER_OFFSET) || defined (ALLOCATE_OUTGOING_ARGS)
#define MUST_ALIGN
#endif

#if ! defined (MUST_ALIGN) && (!defined(STACK_BOUNDARY) || STACK_BOUNDARY < BIGGEST_ALIGNMENT)
#define MUST_ALIGN
#endif

#ifdef MUST_ALIGN

  if (GET_CODE (size) == CONST_INT)
    size = gen_rtx (CONST_INT, VOIDmode,
		    INTVAL (size) + (BIGGEST_ALIGNMENT / BITS_PER_UNIT - 1));
  else
    size = expand_binop (Pmode, add_optab, size,
			 gen_rtx (CONST_INT, VOIDmode,
				  BIGGEST_ALIGNMENT / BITS_PER_UNIT - 1),
			 0, 1, OPTAB_LIB_WIDEN);
#endif

#ifdef SETJMP_VIA_SAVE_AREA
  /* If setjmp restores regs from a save area in the stack frame,
     avoid clobbering the reg save area.  Note that the offset of
     virtual_incoming_args_rtx includes the preallocated stack args space.
     It would be no problem to clobber that, but it's on the wrong side
     of the old save area.  */
  {
    rtx dynamic_offset
      = expand_binop (Pmode, sub_optab, virtual_stack_dynamic_rtx,
		      stack_pointer_rtx, 0, 1, OPTAB_LIB_WIDEN);
    size = expand_binop (Pmode, add_optab, size, dynamic_offset,
			 0, 1, OPTAB_LIB_WIDEN);
  }
#endif /* SETJMP_VIA_SAVE_AREA */

  /* Round the size to a multiple of the required stack alignment.
     Since the stack if presumed to be rounded before this allocation,
     this will maintain the required alignment.

     If the stack grows downward, we could save an insn by subtracting
     SIZE from the stack pointer and then aligning the stack pointer.
     The problem with this is that the stack pointer may be unaligned
     between the execution of the subtraction and alignment insns and
     some machines do not allow this.  Even on those that do, some
     signal handlers malfunction if a signal should occur between those
     insns.  Since this is an extremely rare event, we have no reliable
     way of knowing which systems have this problem.  So we avoid even
     momentarily mis-aligning the stack.  */

  size = round_push (size);

  do_pending_stack_adjust ();

  if (target == 0)
    target = gen_reg_rtx (Pmode);

#ifndef STACK_GROWS_DOWNWARD
  emit_move_insn (target, virtual_stack_dynamic_rtx);
#endif

  /* Perform the required allocation from the stack.  Some systems do
     this differently than simply incrementing/decrementing from the
     stack pointer.  */
#ifdef HAVE_allocate_stack
  if (HAVE_allocate_stack)
    {
      enum machine_mode mode
	= insn_operand_mode[(int) CODE_FOR_allocate_stack][0];

      if (insn_operand_predicate[(int) CODE_FOR_allocate_stack][0]
	  && ! ((*insn_operand_predicate[(int) CODE_FOR_allocate_stack][0])
		(size, mode)))
	size = copy_to_mode_reg (mode, size);

      emit_insn (gen_allocate_stack (size));
    }
  else
#endif
    anti_adjust_stack (size);

#ifdef STACK_GROWS_DOWNWARD
  emit_move_insn (target, virtual_stack_dynamic_rtx);
#endif

#ifdef MUST_ALIGN
  target = expand_divmod (0, CEIL_DIV_EXPR, Pmode, target,
			  gen_rtx (CONST_INT, VOIDmode,
				   BIGGEST_ALIGNMENT / BITS_PER_UNIT),
			  0, 1);

  target = expand_mult (Pmode, target,
			gen_rtx (CONST_INT, VOIDmode,
				 BIGGEST_ALIGNMENT / BITS_PER_UNIT),
			0, 1);
#endif
  
  /* Some systems require a particular insn to refer to the stack
     to make the pages exist.  */
#ifdef HAVE_probe
  if (HAVE_probe)
    emit_insn (gen_probe ());
#endif

  return target;
}

/* Return an rtx representing the register or memory location
   in which a scalar value of data type VALTYPE
   was returned by a function call to function FUNC.
   FUNC is a FUNCTION_DECL node if the precise function is known,
   otherwise 0.  */

rtx
hard_function_value (valtype, func)
     tree valtype;
     tree func;
{
  return FUNCTION_VALUE (valtype, func);
}

/* Return an rtx representing the register or memory location
   in which a scalar value of mode MODE was returned by a library call.  */

rtx
hard_libcall_value (mode)
     enum machine_mode mode;
{
  return LIBCALL_VALUE (mode);
}
