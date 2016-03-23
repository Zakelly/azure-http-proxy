/*
 *    http_proxy_server_connection_context.hpp:
 *
 *    Copyright (C) 2013-2015 limhiaoing <blog.poxiao.me> All Rights Reserved.
 *
 */

#ifndef AZURE_HTTP_PROXY_SERVER_CONNECTION_CONTEXT_HPP
#define AZURE_HTTP_PROXY_SERVER_CONNECTION_CONTEXT_HPP

#include <cstdint>

#include "config.hpp"
#if ASIO_STANDALONE
#include <asio.hpp>
using error_code = asio::error_code;
#else
#include <boost/asio.hpp>
using error_code = boost::system::error_code
#endif

#include "http_chunk_checker.hpp"

namespace azure_proxy {

enum class proxy_connection_state {
    read_cipher_data,
    resolve_origin_server_address,
    connect_to_origin_server,
    tunnel_transfer,
    read_http_request_header,
    write_http_request_header,
    read_http_request_content,
    write_http_request_content,
    read_http_response_header,
    write_http_response_header,
    read_http_response_content,
    write_http_response_content,
    report_connection_established,
    report_error
};

struct http_proxy_server_connection_context {
    proxy_connection_state connection_state;
    bool reconnect_on_error;
    std::string origin_server_name;
    unsigned short origin_server_port;
    std::unique_ptr<asio::ip::tcp::endpoint> origin_server_endpoint;
};

struct http_proxy_server_connection_read_request_context {
    bool is_proxy_client_keep_alive;
    std::uint64_t content_length;
    std::uint64_t content_length_has_read;
    http_chunk_checker chunk_checker;
};

struct http_proxy_server_connection_read_response_context {
    bool is_origin_server_keep_alive;
	std::uint64_t content_length;
    std::uint64_t content_length_has_read;
    http_chunk_checker chunk_checker;
};

} // namespace azure_proxy

#endif
