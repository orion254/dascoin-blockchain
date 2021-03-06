/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <graphene/chain/protocol/chain_parameters.hpp>
#include <graphene/chain/protocol/types.hpp>
#include <graphene/chain/immutable_chain_parameters.hpp>

#include <fc/crypto/sha256.hpp>

#include <string>
#include <vector>

namespace graphene { namespace chain {
using std::string;
using std::vector;

struct genesis_state_type {
   struct initial_account_type {
      initial_account_type(const string& name = string(),
                           const public_key_type& owner_key = public_key_type(),
                           const public_key_type& active_key = public_key_type(),
                           bool is_lifetime_member = false)
         : name(name),
           owner_key(owner_key),
           active_key(active_key == public_key_type()? owner_key : active_key),
           is_lifetime_member(is_lifetime_member)
      {}
      string name;
      public_key_type owner_key;
      public_key_type active_key;
      bool is_lifetime_member = false;
   };
   struct initial_asset_type {
      struct initial_collateral_position {
         address owner;
         share_type collateral;
         share_type debt;
      };

      string symbol;
      string issuer_name;

      string description;
      uint8_t precision = GRAPHENE_BLOCKCHAIN_PRECISION_DIGITS;

      share_type max_supply;
      share_type accumulated_fees;

      bool is_bitasset = false;
      vector<initial_collateral_position> collateral_records;
   };
   struct initial_balance_type {
      address owner;
      string asset_symbol;
      share_type amount;
   };
   struct initial_vesting_balance_type {
      address owner;
      string asset_symbol;
      share_type amount;
      time_point_sec begin_timestamp;
      uint32_t vesting_duration_seconds = 0;
      share_type begin_balance;
   };
   struct initial_issued_cycles_type {
      string owner_name;
      share_type amount;
   };
   struct initial_witness_type {
      /// Must correspond to one of the initial accounts
      string owner_name;
      public_key_type block_signing_key;
   };
   struct initial_committee_member_type {
      /// Must correspond to one of the initial accounts
      string owner_name;
   };
   struct initial_worker_type {
      /// Must correspond to one of the initial accounts
      string owner_name;
      share_type daily_pay;
   };
   struct initial_chain_authority_type {
     /// Must correspond to one of the initial accounts
     string owner_name;
   };
   struct initial_dascoin_price_type {
     share_type base_amount;
     share_type quote_amount;
   };
   struct historic_upgrade_event_type {
     time_point_sec execution_time;
     time_point_sec cutoff_time;
     vector<time_point_sec> subsequent_executions;
     string comment;
   };

   time_point_sec                           initial_timestamp;
   share_type                               max_core_supply = GRAPHENE_MAX_SHARE_SUPPLY;
   share_type                               max_dascoin_supply = DASCOIN_MAX_DASCOIN_SUPPLY;
   frequency_type                           initial_frequency = DASCOIN_INITIAL_FREQUENCY;
   chain_parameters                         initial_parameters;
   immutable_chain_parameters               immutable_parameters;
   vector<initial_account_type>             initial_accounts;
   vector<initial_asset_type>               initial_assets;
   vector<initial_balance_type>             initial_balances;
   vector<initial_vesting_balance_type>     initial_vesting_balances;
   vector<initial_issued_cycles_type>       initial_issued_cycles;
   uint64_t                                 initial_active_witnesses = GRAPHENE_DEFAULT_MIN_WITNESS_COUNT;
   vector<initial_witness_type>             initial_witness_candidates;
   vector<initial_committee_member_type>    initial_committee_candidates;
   vector<initial_worker_type>              initial_worker_candidates;
   vector<historic_upgrade_event_type>      historic_upgrade_events;

   /**
    * Initial chain authorities.
    */
   initial_chain_authority_type             initial_root_authority;
   initial_chain_authority_type             initial_license_administration_authority;
   initial_chain_authority_type             initial_license_issuing_authority;
   initial_chain_authority_type             initial_license_authentication_authority;
   initial_chain_authority_type             initial_webasset_issuing_authority;
   initial_chain_authority_type             initial_webasset_authentication_authority;
   initial_chain_authority_type             initial_cycle_issuing_authority;
   initial_chain_authority_type             initial_cycle_authentication_authority;
   initial_chain_authority_type             initial_registrar;
   initial_chain_authority_type             initial_personal_identity_validation_authority;
   initial_chain_authority_type             initial_wire_out_handler;
   initial_chain_authority_type             initial_daspay_administrator_authority;
   initial_chain_authority_type             initial_das33_administrator_authority;

   /**
    * Initial dascoin price.
    */
   initial_dascoin_price_type               initial_dascoin_price{DASCOIN_DEFAULT_STARTING_PRICE_BASE_AMOUNT,
                                                                  DASCOIN_DEFAULT_STARTING_PRICE_QUOTE_AMOUNT};

   /**
    * Temporary, will be moved elsewhere.
    */
   chain_id_type                          initial_chain_id;

   /**
    * Get the chain_id corresponding to this genesis state.
    *
    * This is the SHA256 serialization of the genesis_state.
    */
   chain_id_type compute_chain_id() const;
};

} } // namespace graphene::chain

FC_REFLECT( graphene::chain::genesis_state_type::initial_account_type,
            (name)
            (owner_key)
            (active_key)
            (is_lifetime_member)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_asset_type,
            (symbol)
            (issuer_name)
            (description)
            (precision)
            (max_supply)
            (accumulated_fees)
            (is_bitasset)
            (collateral_records)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_asset_type::initial_collateral_position,
            (owner)
            (collateral)
            (debt)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_balance_type,
            (owner)
            (asset_symbol)
            (amount)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_vesting_balance_type,
            (owner)
            (asset_symbol)
            (amount)
            (begin_timestamp)
            (vesting_duration_seconds)
            (begin_balance)
          )

FC_REFLECT ( graphene::chain::genesis_state_type::initial_issued_cycles_type,
             (owner_name)
             (amount)
           )

FC_REFLECT( graphene::chain::genesis_state_type::initial_witness_type,
            (owner_name)
            (block_signing_key)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_committee_member_type,
            (owner_name)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_worker_type,
            (owner_name)
            (daily_pay)
          )

FC_REFLECT( graphene::chain::genesis_state_type::historic_upgrade_event_type,
            (execution_time)
            (cutoff_time)
            (subsequent_executions)
            (comment)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_chain_authority_type,
            (owner_name)
          )

FC_REFLECT( graphene::chain::genesis_state_type::initial_dascoin_price_type,
            (base_amount)
            (quote_amount)
          )

FC_REFLECT( graphene::chain::genesis_state_type,
            (initial_timestamp)
            (max_core_supply)
            (max_dascoin_supply)
            (initial_parameters)
            (initial_accounts)
            (initial_assets)
            (initial_balances)
            (initial_frequency)
            (initial_vesting_balances)
            (initial_issued_cycles)
            (initial_active_witnesses)
            (initial_witness_candidates)
            (initial_committee_candidates)
            (initial_worker_candidates)
            (historic_upgrade_events)
            (initial_root_authority)
            (initial_license_administration_authority)
            (initial_license_issuing_authority)
            (initial_license_authentication_authority)
            (initial_webasset_issuing_authority)
            (initial_webasset_authentication_authority)
            (initial_cycle_issuing_authority)
            (initial_cycle_authentication_authority)
            (initial_registrar)
            (initial_personal_identity_validation_authority)
            (initial_wire_out_handler)
            (initial_daspay_administrator_authority)
            (initial_das33_administrator_authority)
            (initial_dascoin_price)
            (initial_chain_id)
            (immutable_parameters)
          )
