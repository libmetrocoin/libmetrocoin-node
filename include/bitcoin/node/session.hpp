/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#ifndef LIBBITCOIN_NODE_SESSION_HPP
#define LIBBITCOIN_NODE_SESSION_HPP

#include <set>
#include <bitcoin/blockchain.hpp>
#include <bitcoin/node/define.hpp>
#include <bitcoin/node/poller.hpp>

namespace libbitcoin {
namespace node {

class BCN_API session
{
public:
    typedef std::function<void (const std::error_code&)> completion_handler;

    session(threadpool& pool, bc::network::handshake& handshake,
        bc::network::protocol& protocol, chain::blockchain& blockchain,
        poller& poller, chain::transaction_pool& transaction_pool);

    void start(completion_handler handle_complete);
    void stop(completion_handler handle_complete);

private:
    void new_channel(const std::error_code& code, 
        bc::network::channel_ptr node);
    void set_start_height(const std::error_code& code, uint64_t fork_point,
        const chain::blockchain::block_list& new_blocks,
        const chain::blockchain::block_list& replaced_blocks);

    void inventory(const std::error_code& code,
        const inventory_type& packet, bc::network::channel_ptr node);
    void get_data(const std::error_code& code,
        const get_data_type& packet, bc::network::channel_ptr node);
    void get_blocks(const std::error_code& code,
        const get_blocks_type& packet, bc::network::channel_ptr node);

    void new_tx_inventory(const hash_digest& tx_hash,
        bc::network::channel_ptr node);
    void request_tx_data(bool tx_exists,
        const hash_digest& tx_hash, bc::network::channel_ptr node);

    boost::asio::io_service::strand strand_;
    bc::network::handshake& handshake_;
    bc::network::protocol& protocol_;
    chain::blockchain& chain_;
    poller& poll_;
    chain::transaction_pool& tx_pool_;
};

} // namespace node
} // namespace libbitcoin

#endif

