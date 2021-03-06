/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-node.
 *
 * libbitcoin-node is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_NODE_LOGGING_HPP
#define LIBBITCOIN_NODE_LOGGING_HPP

#include <iostream>
#include <string>
#include <bitcoin/node/define.hpp>

namespace libbitcoin {
namespace node {

#define LOG_NODE "node"

void BCN_API initialize_logging(std::ofstream& debug_log,
    std::ofstream& error_log, std::ostream& output, std::ostream& error,
    const std::string& skip_domain="");

} // namespace node
} // namespace libbitcoin

#endif