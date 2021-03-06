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

#include "util.h"

#include <cerrno>
#include <sys/stat.h>


namespace bitz {

	namespace util {

		RequestHandler * find_req_handler( req_handlers_t req_handlers, const std::string &req_method ) throw() {

			RequestHandler * req_handler;
			req_handlers_index_t rh_i;
			rh_i = req_handlers.find( req_method );

			if ( rh_i != req_handlers.end() ) {
				req_handler = rh_i->second;
			} else {
				req_handler = NULL;
			}

			return req_handler;

		}


		void delete_req_handlers( req_handlers_t req_handlers ) throw() {

			req_handlers_index_t rh_i;

			for ( rh_i = req_handlers.begin(); rh_i != req_handlers.end(); rh_i++ ) {
				if ( rh_i->first != "OPTIONS" ) {
					delete rh_i->second;
				}
			}

			return;

		}


		std::string dirpath( const std::string &path ) throw() {
			return path.substr( 0, path.find_last_of( '/' ) );
		}


		std::string filename( const std::string &path ) throw() {
			return path.substr( path.find_last_of( '/' ) );
		}


		bool mkdirp( const std::string &path ) throw() {

			bool r_success = false;


			if ( ::mkdir( path.c_str(), 0755 ) == -1 ) {

				switch( errno ) {

					case ENOENT:

						// parent didn't exist, try to create it
						if ( mkdirp( path.substr( 0, path.find_last_of( '/' ) ) ) ) {

							// try creating the dir again
							r_success = ( 0 == ::mkdir( path.c_str(), 0755 ) );

						} else {

							// failed to create parent
							r_success = false;
						}

						break;

					case EEXIST:

						// already exists
						r_success = true;
						break;

					default:
						r_success = false;
						break;

				}

			} else {
				r_success = true;
			}


			return r_success;

		}


	} /* end of namespace util */

} /* end of namespace bitz */

