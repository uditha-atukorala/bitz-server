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

#ifndef BITZ_REQUEST_MODIFIER_H
#define BITZ_REQUEST_MODIFIER_H

#include <icap/request.h>
#include <icap/response.h>

#include "modifier.h"


namespace bitz {

	class RequestModifier : public Modifier {
	public:
		RequestModifier();
		virtual ~RequestModifier();

		virtual icap::Response * check( icap::Request * request ) throw() =0;
		virtual icap::Response * preview( icap::RequestHeader * req_header ) throw() =0;

	private:

	};

} /* end of namespace bitz */


/* types of the class factories */
typedef bitz::RequestModifier * reqmod_create_t();
typedef void reqmod_destroy_t( bitz::RequestModifier * );

#endif /* !BITZ_REQUEST_MODIFIER_H */

