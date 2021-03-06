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
#include <bitcoin/node/logging.hpp>

#include <iostream>
#include <string>
#include <boost/date_time.hpp>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>

namespace libbitcoin {
namespace node {

using namespace bc;
using namespace boost::posix_time;
using boost::format;

static std::string make_log_string(log_level level,
    const std::string& domain, const std::string& body, 
    const std::string& skip_domain)
{
    const static auto form = "%1% %2% [%3%] %4%";

    if (body.empty())
        return "";

    if (domain == skip_domain)
        return "";

    const auto log = level_repr(level);
    const auto time = microsec_clock::local_time().time_of_day();
    const auto message = format(form) % time % log % domain % body;
    return message.str();
}

static void log_to_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body, 
    const std::string& skip_domain)
{
    std::string output;
    output = make_log_string(level, domain, body, skip_domain);
    if (!output.empty())
        file << output << std::endl;
}

static void log_to_both(std::ostream& device, std::ofstream& file,
    log_level level, const std::string& domain, const std::string& body,
    const std::string& skip_domain)
{
    std::string output;
    output = make_log_string(level, domain, body, skip_domain);
    if (!output.empty())
    {
        device << output << std::endl;
        file << output << std::endl;
    }
}

static void output_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body,
    const std::string& skip_domain)
{
    log_to_file(file, level, domain, body, skip_domain);
}

static void output_both(std::ofstream& file, std::ostream& output,
    log_level level, const std::string& domain, const std::string& body,
    const std::string& skip_domain)
{
    log_to_both(output, file, level, domain, body, skip_domain);
}

static void error_file(std::ofstream& file, log_level level,
    const std::string& domain, const std::string& body,
    const std::string& skip_domain)
{
    log_to_file(file, level, domain, body, skip_domain);
}

static void error_both(std::ofstream& file, std::ostream& error,
    log_level level, const std::string& domain, const std::string& body,
    const std::string& skip_domain)
{
    log_to_both(error, file, level, domain, body, skip_domain);
}

void initialize_logging(std::ofstream& debug_log, std::ofstream& error_log,
    std::ostream& output, std::ostream& error, const std::string& skip_domain)
{
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;

    // debug|info => debug_log
    log_debug().set_output_function(std::bind(output_file,
        std::ref(debug_log), _1, _2, _3, skip_domain));
    log_info().set_output_function(std::bind(output_both,
        std::ref(debug_log), std::ref(output), _1, _2, _3, skip_domain));

    // warning|error|fatal => error_log + console
    log_warning().set_output_function(std::bind(error_file,
        std::ref(error_log), _1, _2, _3, skip_domain));
    log_error().set_output_function(std::bind(error_both,
        std::ref(error_log), std::ref(error), _1, _2, _3, skip_domain));
    log_fatal().set_output_function(std::bind(error_both,
        std::ref(error_log), std::ref(error), _1, _2, _3, skip_domain));
}

} // namespace node
} // namespace libbitcoin