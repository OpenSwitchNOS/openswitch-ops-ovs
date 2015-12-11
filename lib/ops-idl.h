/*
 * Copyright (C) 2015 Hewlett-Packard Development Company, L.P.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OPS_IDL_H
#define OPS_IDL_H 1

#ifdef  __cplusplus
extern "C" {
#endif

#define ovsrec_open_vswitch ovsrec_system
#define ovsrec_table_open_vswitch ovsrec_table_system

#define ovsrec_open_vswitch_columns ovsrec_system_columns
#define ovsrec_open_vswitch_get_for_uuid ovsrec_system_get_for_uuid
#define ovsrec_open_vswitch_first ovsrec_system_first
#define ovsrec_open_vswitch_next ovsrec_system_next
#define ovsrec_open_vswitch_init ovsrec_system_init
#define ovsrec_open_vswitch_delete ovsrec_system_delete
#define ovsrec_open_vswitch_insert ovsrec_system_insert
#define OVSREC_OPEN_VSWITCH_FOR_EACH OVSREC_SYSTEM_FOR_EACH
#define OVSREC_OPEN_VSWITCH_FOR_EACH_SAFE OVSREC_SYSTEM_FOR_EACH_SAFE

#define ovsrec_open_vswitch_verify_bridges ovsrec_system_verify_bridges
#define ovsrec_open_vswitch_set_bridges ovsrec_system_set_bridges
#define ovsrec_open_vswitch_col_bridges ovsrec_system_col_bridges
#define ovsrec_open_vswitch_col_subsystems ovsrec_system_col_subsystems
#define ovsrec_open_vswitch_col_manager_options ovsrec_system_col_manager_options
#define ovsrec_open_vswitch_col_vrfs ovsrec_system_col_vrfs
#define ovsrec_open_vswitch_col_ssl ovsrec_system_col_ssl
#define ovsrec_open_vswitch_set_manager_options ovsrec_system_set_manager_options
#define ovsrec_open_vswitch_set_ssl ovsrec_system_set_ssl
#define ovsrec_open_vswitch_verify_vrfs ovsrec_system_verify_vrfs
#define ovsrec_open_vswitch_set_vrfs ovsrec_system_set_vrfs
#define ovsrec_open_vswitch_verify_manager_options ovsrec_system_verify_manager_options
#define ovsrec_open_vswitch_verify_ssl ovsrec_system_verify_ssl
#define ovsrec_open_vswitch_col_cur_cfg ovsrec_system_col_cur_cfg
#define ovsrec_open_vswitch_col_next_cfg ovsrec_system_col_next_cfg


#define OVSREC_BGP_ROUTE_ADDRESS_FAMILY_IPV4       "ipv4"
#define OVSREC_BGP_ROUTE_ADDRESS_FAMILY_IPV6       "ipv6"
#define OVSREC_NEIGHBOR_ADDRESS_FAMILY_IPV4        "ipv4"
#define OVSREC_NEIGHBOR_ADDRESS_FAMILY_IPV6        "ipv6"

#define OVSREC_INTERFACE_ADMIN_STATE_DOWN          "down"
#define OVSREC_INTERFACE_ADMIN_STATE_UP            "up"

#define OVSREC_INTERFACE_DUPLEX_FULL               "full"
#define OVSREC_INTERFACE_DUPLEX_HALF               "half"

#define OVSREC_INTERFACE_LINK_STATE_DOWN           "down"
#define OVSREC_INTERFACE_LINK_STATE_UP             "up"

#define OVSREC_INTERFACE_PAUSE_NONE                "none"
#define OVSREC_INTERFACE_PAUSE_RX                  "rx"
#define OVSREC_INTERFACE_PAUSE_RXTX                "rxtx"
#define OVSREC_INTERFACE_PAUSE_TX                  "tx"

#define OVSREC_BUFMON_STATUS_NOT_PROPERLY_CONFIGURED "not-properly-configured"
#define OVSREC_BUFMON_STATUS_OK                    "ok"
#define OVSREC_BUFMON_STATUS_TRIGGERED             "triggered"

enum ovsrec_bufmon_status_e {
    BUFMON_STATUS_NOT_PROPERLY_CONFIGURED,
    BUFMON_STATUS_OK,
    BUFMON_STATUS_TRIGGERED
};

#define OVSREC_VLAN_OPER_STATE_DOWN                "down"
#define OVSREC_VLAN_OPER_STATE_UNKNOWN             "unknown"
#define OVSREC_VLAN_OPER_STATE_UP                  "up"

#define OVSREC_VLAN_OPER_STATE_REASON_ADMIN_DOWN   "admin_down"
#define OVSREC_VLAN_OPER_STATE_REASON_NO_MEMBER_PORT "no_member_port"
#define OVSREC_VLAN_OPER_STATE_REASON_OK           "ok"
#define OVSREC_VLAN_OPER_STATE_REASON_UNKNOWN      "unknown"

#define OVSREC_IDL_ANY_TABLE_ROWS_INSERTED(ovsrec_row_struct, my_seqno) \
(ovsrec_row_struct->header_.table->change_seqno[OVSDB_IDL_CHANGE_INSERT] \
    >= my_seqno)
#define OVSREC_IDL_ANY_TABLE_ROWS_MODIFIED(ovsrec_row_struct, my_seqno) \
(ovsrec_row_struct->header_.table->change_seqno[OVSDB_IDL_CHANGE_MODIFY] \
    >= my_seqno)
#define OVSREC_IDL_ANY_TABLE_ROWS_DELETED(ovsrec_row_struct, my_seqno) \
(ovsrec_row_struct->header_.table->change_seqno[OVSDB_IDL_CHANGE_DELETE] \
    > my_seqno)
#define OVSREC_IDL_IS_ROW_INSERTED(ovsrec_row_struct, my_seqno) \
(ovsrec_row_struct->header_.change_seqno[OVSDB_IDL_CHANGE_INSERT] > my_seqno)
#define OVSREC_IDL_IS_ROW_MODIFIED(ovsrec_row_struct, my_seqno) \
(ovsrec_row_struct->header_.change_seqno[OVSDB_IDL_CHANGE_MODIFY] > my_seqno)
#define OVSREC_IDL_IS_COLUMN_MODIFIED(ovsrec_col_struct, my_seqno) (1)

#ifdef  __cplusplus
}
#endif

#endif /* ops-idl.h */
