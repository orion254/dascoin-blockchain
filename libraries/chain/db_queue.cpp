/**
 * DASCOIN!
 */

#include <graphene/chain/database.hpp>

#include <graphene/chain/queue_objects.hpp>

#include <fc/optional.hpp>

namespace graphene {
namespace chain {

object_id_type database::push_queue_submission(const string& origin, optional<license_type_id_type> license,
                                               account_id_type account, share_type amount, share_type frequency,
                                               const string& comment)
{
    share_type historic_sum = 0;
    auto dascoin_amount = cycles_to_dascoin(amount, frequency);

    const auto& queue = get_index_type<reward_queue_index>().indices().get<by_time>();
    if ( queue.size() == 0 ) {
        historic_sum = get_dynamic_global_properties().total_dascoin_minted + dascoin_amount;
    } else {
        const auto last_el_it = queue.rbegin();
        historic_sum = last_el_it->historic_sum + dascoin_amount;
    }

    return create<reward_queue_object>([&](reward_queue_object& rqo) {
               rqo.origin = origin;
               rqo.license = license;
               rqo.account = account;
               rqo.amount = amount;
               rqo.frequency = frequency;
               rqo.time = head_block_time();
               rqo.comment = comment;
               rqo.historic_sum = historic_sum;
           })
        .id;
}


}  // namespace chain
}  // namespace graphene
