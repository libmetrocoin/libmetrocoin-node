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
#ifndef LIBBITCOIN_NODE_GETX_RESPONDER_HPP
#define LIBBITCOIN_NODE_GETX_RESPONDER_HPP

#include <system_error>
#include <bitcoin/blockchain.hpp>
#include <bitcoin/node/define.hpp>

namespace libbitcoin {
namespace node {

class BCN_API getx_responder
{
public:
    getx_responder(chain::blockchain& chain, chain::transaction_pool& txpool);
    void monitor(bc::network::channel_ptr node);

private:
    // We use this object to keep track of the hash_continue and add
    // a shared state to our channel object.
    struct channel_with_state
    {
        bc::network::channel_ptr node;
        hash_digest hash_continue = null_hash;
    };

    void receive_get_data(const std::error_code& code,
        const get_data_type& packet, channel_with_state special);

    void pool_tx(const std::error_code& code, const transaction_type& tx,
        const hash_digest& tx_hash, bc::network::channel_ptr node);

    void chain_tx(const std::error_code& code,
        const transaction_type& tx, bc::network::channel_ptr node);

    void send_block(const std::error_code& code,
        const block_type& block, bc::network::channel_ptr node);

    chain::blockchain& chain_;
    chain::transaction_pool& txpool_;
};

} // node
} // libbitcoin

#endif

