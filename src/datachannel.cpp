/**
 * Copyright (c) 2019-2021 Paul-Louis Ageneau
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "datachannel.hpp"
#include "common.hpp"
#include "peerconnection.hpp"

#include "impl/datachannel.hpp"
#include "impl/internals.hpp"
#include "impl/peerconnection.hpp"

#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

namespace rtc {

DataChannel::DataChannel(impl_ptr<impl::DataChannel> impl)
    : CheshireCat<impl::DataChannel>(impl),
      Channel(std::dynamic_pointer_cast<impl::Channel>(impl)) {}

DataChannel::~DataChannel() { close(); }

void DataChannel::close() { return impl()->close(); }

uint16_t DataChannel::stream() const { return impl()->stream(); }

uint16_t DataChannel::id() const { return impl()->stream(); }

string DataChannel::label() const { return impl()->label(); }

string DataChannel::protocol() const { return impl()->protocol(); }

Reliability DataChannel::reliability() const { return impl()->reliability(); }

bool DataChannel::isOpen(void) const { return impl()->isOpen(); }

bool DataChannel::isClosed(void) const { return impl()->isClosed(); }

size_t DataChannel::maxMessageSize() const { return impl()->maxMessageSize(); }

bool DataChannel::send(message_ptr data) { return impl()->outgoing(data); }

bool DataChannel::send(message_variant data) { return send(make_message(std::move(data))); }

bool DataChannel::send(const byte *data, size_t size) {
	return send(std::make_shared<Message>(data, data + size, Message::Binary));
}

} // namespace rtc
