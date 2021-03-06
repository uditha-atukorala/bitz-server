/*
 *	bitz-server, An ICAP server implementation in C++
 *	Copyright (C) 2012	Uditha Atukorala
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef BITZ_MODIFIER_H
#define BITZ_MODIFIER_H

#include <icap/request.h>
#include <icap/response.h>


namespace bitz {

	class Modifier {
	public:

		/* types of the class factories */
		typedef bitz::Modifier * create_t();
		typedef void destroy_t( bitz::Modifier * );

		struct symbols_t {
			void * modifier;
			create_t  * create;
			destroy_t * destroy;
		};

		Modifier();
		virtual ~Modifier();

		/**
		*   Modify the request as needed and return a response object.
		*
		*   @param request request object
		*   @return response object
		*/
		virtual icap::Response * modify( icap::Request * request ) throw() =0;

		/**
		*   Preview the request passed in and return a response object. The
		*   response status of 100 (continue) should be handled by the caller
		*   and pass the complete request to modify() method.
		*
		*   @param request request object
		*   @return response object
		*/
		virtual icap::Response * preview( icap::Request * request ) throw() =0;

	private:

	};

} /* end of namespace bitz */

#endif /* !BITZ_MODIFIER_H */

