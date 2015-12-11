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

#ifndef OPS_OFPROTO_OFPROTO_PROVIDER_H
#define OPS_OFPROTO_OFPROTO_PROVIDER_H 1

#include "ofproto/ofproto-provider.h"
#include "ops-ofproto.h"

#if 0
struct ops_ofproto {
    struct ofproto _base;

    /* VLAN support. */
    unsigned long int *vlans_bmp;  /* Bitmap of all configured VLANs. */
};
#endif

struct ops_ofproto_class {
    struct ofproto_class _base;

    /* Retrieves information about bundle on 'ofproto'.
     *
     * Stores bundle information for 'ofproto' in 'bundle_handle'. */
    int (*bundle_get)(struct ofproto *ofproto, void *aux, int *bundle_handle);

    /* Configures VLANs.
     *
     * This function affects only the behavior of the OFPP_NORMAL action.  An
     * implementation that does not support it may set it to NULL or return
     * EOPNOTSUPP. */
    int (*set_vlan)(struct ofproto *ofproto, int vid, bool add);

    /* Add L3 host entry. */
    int (*add_l3_host_entry)(const struct ofproto *ofproto, void *aux,
                             bool is_ipv6_addr, char *ip_addr,
                             char *next_hop_mac_addr, int *l3_egress_id);

    /* Delete L3 host entry. */
    int (*delete_l3_host_entry)(const struct ofproto *ofproto, void *aux,
                                bool is_ipv6_addr, char *ip_addr,
                                int *l3_egress_id);

    /* Get L3 host hit bit. */
    int (*get_l3_host_hit)(const struct ofproto *ofproto, void *aux,
                           bool is_ipv6_addr, char *ip_addr, bool *hit_bit);

    /* Add/Delete/Modify routes */
    int (*l3_route_action)(const struct ofproto *ofproto,
                           enum ofproto_route_action action,
                           struct ofproto_route *route);

    /* Enable/Disable ECMP */
    int (*l3_ecmp_set)(const struct ofproto *ofproto, bool enable);

    /* Enable/Disable ECMP hash config */
    int (*l3_ecmp_hash_set)(const struct ofproto *ofproto, unsigned int hash,
                            bool enable);
};

#endif /* ofproto/ops-ofproto-provider.h */
