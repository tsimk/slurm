/****************************************************************************\
 *  arg_desc.h
 *****************************************************************************
 *  Copyright (C) 2005 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  UCRL-CODE-217948.
 *
 *  This file is part of SLURM, a resource management program.
 *  For details, see <http://www.llnl.gov/linux/slurm/>.
 *
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
\****************************************************************************/
#ifndef __ARG_DESC_H__
#define __ARG_DESC_H__

/*
 * An argument descriptor is a named positional parameter in an
 * argv-like vector of arguments.  An array of named parameters
 * constitutes the descriptor, and the index (zero-based) in the
 * array of the named parameter is also its index in the argument
 * vector.
 *
 * The descriptor array must be terminated by an entry whose name
 * is the NULL pointer.
 *
 *	arg_desc_t arg_desc[] = {
 *		{ "foo" },
 *		{ "bar" },
 *		{ NULL }
 *	};
 *
 * For vectors which are finalized at initialization, the receiving
 * functions can call arg_idx_by_name() and cache the value in
 * order to accelerate argument processing.
 *
 * For well-defined APIs containing explicit initialization routines,
 * this can be done at initialization, as in
 *
 *	void init( arg_desc_t *desc )
 *	{
 *		static_foo_idx = arg_idx_by_name( desc, "foo" );
 *	}
 *
 *	void need_foo( void *argv[] )
 *	{
 *		foo_type foo = (foo_type) argv[ static_foo_idx ];
 *		...
 *	}
 *
 * For vectors which may vary for each invocation of the function,
 * it is best to pass the argument descriptor array as a first-class
 * parameter to the function:
 *
 *	void need_foo_dynamic( arg_desc_t *desc, void *argv[] )
 *	{
 *		int idx = arg_idx_by_name( desc, "foo" );
 *		foo_type foo = (foo_type) argv[ idx ];
 *	}
 */

typedef struct _arg_desc {
    char *name;
} arg_desc_t;

/*
 * Return the number of argument names in the descriptor.
 */
const int arg_count( const arg_desc_t *desc );

/*
 * Return the index in the descriptor corresponding to the name.
 *
 * Returns -1 if the name can't be found.
 */
const int arg_idx_by_name( const arg_desc_t *desc, const char *name );

/*
 * Return the name of the argument for the given index, or NULL if
 * the index is invalid.
 */
const char *arg_name_by_idx( const arg_desc_t *desc, const int idx );

#endif /*__ARG_DESC_H__*/
