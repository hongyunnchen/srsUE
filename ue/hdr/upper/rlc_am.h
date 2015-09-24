/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2015 The srsUE Developers. See the
 * COPYRIGHT file at the top-level directory of this distribution.
 *
 * \section LICENSE
 *
 * This file is part of the srsUE library.
 *
 * srsUE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsUE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#ifndef RLC_AM_H
#define RLC_AM_H

#include "common/log.h"
#include "common/common.h"
#include "common/msg_queue.h"
#include "upper/rlc_entity.h"

namespace srsue {

class rlc_am
    :public rlc_entity
{
public:
  rlc_am();
  void init(srslte::log *rlc_entity_log_, uint32_t lcid_);
  void configure(LIBLTE_RRC_RLC_CONFIG_STRUCT *cnfg);

  RLC_MODE_ENUM get_mode();
  uint32_t      get_bearer();

  // PDCP interface
  void write_sdu(srsue_byte_buffer_t *sdu);
  bool try_read_sdu(srsue_byte_buffer_t *sdu);

  // MAC interface
  uint32_t get_buffer_state();
  int      read_pdu(uint8_t *payload, uint32_t nof_bytes);
  void     write_pdu(uint8_t *payload, uint32_t nof_bytes);

private:

  srslte::log *log;
  uint32_t     lcid;

  // UL configs
  int32_t    t_poll_retx;      // Poll retx timeout (ms)
  int32_t    poll_pdu;         // Insert poll bit after this many PDUs
  int32_t    poll_byte;        // Insert poll bit after this much data (KB)
  int32_t    max_retx_thresh;  // Max number of retx

  // DL configs
  int32_t   t_reordering;     // Timer used by rx to detect PDU loss  (ms)
  int32_t   t_status_prohibit;// Timer used by rx to prohibit tx of status PDU (ms)

  // Thread-safe queues for MAC messages
  msg_queue    ul_queue;
  msg_queue    dl_queue;
};

} // namespace srsue


#endif // RLC_AM_H