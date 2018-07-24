
#include "evloop.h"

#include <uv.h>
#include <cstdlib>


namespace bitz {

	EvLoop::EvLoop() {
		_loop = std::make_unique<uv_loop_t>();
		uv_loop_init( _loop.get() );

		// logger
		_logger = spdlog::get( "bitz-server" );
	}


	EvLoop::~EvLoop() {
		//
	}


	uv_loop_t* EvLoop::loop() {
		return _loop.get();
	}


	void EvLoop::run() {
		uv_run( _loop.get(), UV_RUN_DEFAULT );
	}


	void EvLoop::start( unsigned short port, const std::string &address, int backlog ) {
		struct sockaddr_in saddr;
		int r;

		_server = std::make_unique<uv_tcp_t>();
		_server->data = this;

		r = uv_ip4_addr( address.c_str(), port, &saddr );
		if ( r != 0 ) {
			// TODO: exception
		}

		r = uv_tcp_init( _loop.get(), _server.get() );
		if ( r != 0 ) {
			// TODO: exception
		}

		r = uv_tcp_bind( _server.get(), reinterpret_cast<const struct sockaddr*>( &saddr ), 0 );
		if ( r != 0 ) {
			// TODO: exception
		}

		r = uv_listen( reinterpret_cast<uv_stream_t*>( _server.get() ), backlog, connection_cb );
		if ( r != 0 ) {
			// TODO: exception
		}
	}


	void EvLoop::stop() {
		uv_stop( _loop.get() );
		uv_loop_close( _loop.get() );
	}


	void EvLoop::alloc_cb( uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf ) {
		buf->base = static_cast<char*>( std::malloc( suggested_size ) );
		buf->len = suggested_size;
	}


	void EvLoop::connection_cb( uv_stream_t* server, int status ) {
		EvLoop* evloop = static_cast<EvLoop*>( server->data );
		uv_tcp_t* stream = new uv_tcp_t();
		int r;

		r = uv_tcp_init( evloop->loop(), stream );
		if ( r != 0 ) {
			// TODO: exception
		}

		stream->data = new icap_data_t();
		r = uv_accept( server, reinterpret_cast<uv_stream_t*>( stream ) );
		if ( r != 0 ) {
			// TODO: exception
		}

		r = uv_read_start( reinterpret_cast<uv_stream_t*>( stream ), alloc_cb, read_cb );
		if ( r != 0 ) {
			// TODO: exception
		}
	}


	void EvLoop::read_cb( uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf ) {
		if ( nread <= 0 && buf->base != nullptr ) {
			std::free( buf->base );
		}

		if ( nread == 0 ) { return; }

		if ( nread < 0 ) {
			// TODO: handle errors
			uv_read_stop( stream );
			return;
		}

		// read data
		auto data = static_cast<icap_data_t*>( stream->data );
		if ( !data->request ) {
			data->request = std::make_shared<icap::Request>();
		}

		data->request->read( buf->base, nread );
	}


	void EvLoop::shutdown_cb( uv_shutdown_t* req, int status ) {
		// TODO: free memory for stream->data (icap_data_t)
	}

} /* end of namespace bitz */
