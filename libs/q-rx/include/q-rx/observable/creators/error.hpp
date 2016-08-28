/*
 * Copyright 2016 Gustaf Räntilä
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBQ_RX_OBSERVABLE_CREATORS_ERROR_HPP
#define LIBQ_RX_OBSERVABLE_CREATORS_ERROR_HPP

namespace q { namespace rx {

template< typename T >
inline observable< T >
observable< T >::
error( const q::queue_ptr& queue, std::exception_ptr exception )
{
	q::channel< T > channel_( queue, 0 );
	channel_.get_writable( ).close( std::move( exception ) );
	return observable< T >( channel_ );
}

template< typename T >
template< typename Exception >
inline typename std::enable_if<
	!std::is_same<
		typename std::decay< Exception >::type,
		std::exception_ptr
	>::value,
	observable< T >
>::type
observable< T >::
error( const q::queue_ptr& queue, Exception&& exception )
{
	return error( queue, std::make_exception_ptr(
		std::forward< Exception >( exception ) ) );
}

} } // namespace rx, namespace q

#endif // LIBQ_RX_OBSERVABLE_CREATORS_ERROR_HPP