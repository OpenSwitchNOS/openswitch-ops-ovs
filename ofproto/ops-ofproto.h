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

#ifndef OPS_OFPROTO_H
#define OPS_OFPROTO_H 1

#include "ofproto/ofproto.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct bfd_cfg;
struct cfm_settings;
struct cls_rule;
struct netdev;
struct netdev_stats;
struct ofport;
struct ofproto;
struct shash;
struct simap;

/* FIXME: Use MAX_NEXTHOPS_PER_ROUTE from common header */
#define OFPROTO_MAX_NH_PER_ROUTE    32 /* maximum number of nexthops per route.
                                          only consider non-weighted ECMP now */
enum ofproto_route_family {
    OFPROTO_ROUTE_IPV4,
    OFPROTO_ROUTE_IPV6
};

enum ofproto_route_action {
    OFPROTO_ROUTE_ADD,
    OFPROTO_ROUTE_DELETE,
    OFPROTO_ROUTE_DELETE_NH
};

enum ofproto_nexthop_state {
    OFPROTO_NH_UNRESOLVED,
    OFPROTO_NH_RESOLVED
};

enum ofproto_nexthop_type {
    OFPROTO_NH_IPADDR,
    OFPROTO_NH_PORT
};

struct ofproto_route_nexthop {
    char *id;                         /* IP address or Port name */
    enum ofproto_nexthop_type type;
    enum ofproto_nexthop_state state; /* is arp resolved for this next hop */
    int  rc;                          /* rc = 0 means success */
    const char *err_str;              /* set if rc != 0 */
    int  l3_egress_id;
};

struct ofproto_route {
    enum ofproto_route_family family;
    char *prefix;

    uint8_t  n_nexthops;              /* number of nexthops */
    struct ofproto_route_nexthop nexthops[OFPROTO_MAX_NH_PER_ROUTE]; /* nexthops */
};

/* ECMP hash bit-fields */
#define OFPROTO_ECMP_HASH_SRCPORT        0x1     /* destination L4 port */
#define OFPROTO_ECMP_HASH_DSTPORT        0x2     /* source L4 port */
#define OFPROTO_ECMP_HASH_SRCIP          0x4     /* source IP v4/v6 */
#define OFPROTO_ECMP_HASH_DSTIP          0x8     /* source IP v4/v6 */

enum ofproto_host_action {
    OFPROTO_HOST_ADD,
    OFPROTO_HOST_DELETE,
    OFPROTO_NEIGHBOR_ADD,
    OFPROTO_NEIGHBOR_MODIFY,
    OFPROTO_NEIGHBOR_DELETE
};

struct ofproto_l3_host {
    bool family;                      /* Type of host */
    char *ip_address;                 /* V4/6 IP address (prefix/len)*/
    int  rc;                          /* rc = 0 means success */
    const char *err_str;              /* set if rc != 0 */
    char *mac;                        /* These are for neighbor, mac */
    int  l3_egress_id;                /* Egress ID in case if we need */
};

/* Port option configuration list */
enum port_option_args {
    /* Port vlan configuration option change */
    PORT_OPT_VLAN,

    /* Port Bond (LAG) configuration option change */
    PORT_OPT_BOND,

    /* hw_config driven mostly by l3portd */
    PORT_HW_CONFIG,

    /* Array size */
    PORT_OPT_MAX
};

/* Indicate whether port primary/secondary v4/v6 ip is changed */
#define PORT_PRIMARY_IPv4_CHANGED     0x1
#define PORT_PRIMARY_IPv6_CHANGED     0x2
#define PORT_SECONDARY_IPv4_CHANGED   0x4
#define PORT_SECONDARY_IPv6_CHANGED   0x8

/* Configuration of bundles. */
struct ops_ofproto_bundle_settings {
    struct ofproto_bundle_settings _base;

    const struct smap *port_options[PORT_OPT_MAX];  /* Port options list */
    bool hw_bond_should_exist;    /* Indicates if a bond should exist in h/w
                                     for this bundle.  If hw_bond_handle exists
                                     but this variable is false, it indicates
                                     the h/w bond should be deleted. */
    bool bond_handle_alloc_only;  /* Allocate a bond hanlde and return.
                                     This flag is set to true when a bond
                                     entry is initially created without
                                     active slave members. */
    ofp_port_t *slaves_tx_enable; /* OpenFlow port numbers for slaves in
                                     tx_enable state. */
    size_t n_slaves_tx_enable;    /* Number of slaves in tx_enable state. */
    size_t slaves_entered;         /* Number of slaves entered while adding a bond*/
    int  ip_change;
    char *ip4_address;
    char *ip6_address;
    size_t n_ip4_address_secondary;
    char **ip4_address_secondary; /* List of secondary IP address */
    size_t n_ip6_address_secondary;
    char **ip6_address_secondary; /* List of secondary IPv6 address */
    bool enable;                  /* Port enable */
};

int ofproto_bundle_get(struct ofproto *, void *aux, int *bundle_handle);
/* Configuration of VLANs. */
int ofproto_set_vlan(struct ofproto *, int vid, bool add);

int ofproto_add_l3_host_entry(struct ofproto *ofproto, void *aux,
                              bool is_ipv6_addr, char *ip_addr,
                              char *next_hop_mac_addr, int *l3_egress_id);

int ofproto_delete_l3_host_entry(struct ofproto *ofproto, void *aux,
                             bool is_ipv6_addr, char *ip_addr,
                             int *l3_egress_id);

int ofproto_get_l3_host_hit(struct ofproto *ofproto, void *aux,
                            bool addr_type, char *ip_addr, bool *hit_bit);
int ofproto_l3_route_action(struct ofproto *ofproto,
                            enum ofproto_route_action action,
                            struct ofproto_route *route);

int ofproto_l3_ecmp_set(struct ofproto *ofproto, bool enable);
int ofproto_l3_ecmp_hash_set(struct ofproto *ofproto, unsigned int hash,
                             bool enable);

#ifdef  __cplusplus
}
#endif

#endif /* ops-ofproto.h */
