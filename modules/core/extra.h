/***************************************************************************
                          external.h  -  description
                             -------------------
    begin                : Fri Nov 9 2001
    copyright            : (C) 2001 by Matt Sabins
    email                : sabinsmh@clarkson.edu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

 #ifndef _EXTERNAL_H_
 #define _EXTERNAL_H_
	
	#include <pthread.h>


	typedef enum {
		L_STATIC_WRITE,		//A write to a static named data variable
		L_STATIC_READ,		//A read from a static named data variable
		L_DYNAMIC_WRITE,	//A write to a pointered to variable.
		L_DYNAMIC_READ,		//A read from a pointed variable.
	}line_type_e;

	typedef unsigned int memaddr_t;

	void construct_locksmith(unsigned int approx_thread_num);
	void destroy_locksmith();
	void locksmith_dump_lock_info();
	void locksmith_remove_lock_from_thread(pthread_mutex_t* mutex) __attribute__ ((regparm(3)));
	void locksmith_add_lock_to_thread(pthread_mutex_t* mutex) __attribute__ ((regparm(3)));
	void locksmith_add_memory_access(pthread_t thread,memaddr_t addr,line_type_e type,int lineno,char* source);
	
 #endif
