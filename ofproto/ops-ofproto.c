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


#include <errno.h>
#include "openvswitch/vlog.h"
#include "ops-ofproto-provider.h"
#include "vlan-bitmap.h"

VLOG_DEFINE_THIS_MODULE(ofproto);

#if 0
#include "plugins.h"

int
ops_ofproto_create(const char *datapath_name, const char *datapath_type,
               struct ops_ofproto **ops_ofprotop)
{
    struct ofproto *ofprotop;

    ofproto_create(datapath_name, datapath_type, &ofprotop);
    if (*ofprotop) {
        ofproto->vlans_bmp = bitmap_allocate(VLAN_BITMAP_SIZE);
    }
    return 0; 
}

void
ops_ofproto_destroy(struct ofproto *p)
    OVS_EXCLUDED(ofproto_mutex)
{
    if (!p) {
        return;
    }

    bitmap_free(p->vlans_bmp);
    ofproto_destroy(p);
}
#endif

/* Retrieves bundle information in 'ofproto'.
 * Stores bundle handle in 'bundle_handle'. */
int
ofproto_bundle_get(struct ofproto *ofproto, void *aux,
                   int *bundle_handle)
{
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    if (!s->bundle_get) {
        *bundle_handle = -1;
        return EOPNOTSUPP;
    }

    return s->bundle_get(ofproto, aux, bundle_handle);
}


/* VLANs. */
int
ofproto_set_vlan(struct ofproto *ofproto, int vid, bool add)
{
    int rc = 0;
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    if (s->set_vlan) {
        rc = s->set_vlan(ofproto, vid, add);
        if (rc == 0) {
            bitmap_set(ofproto->vlan_bitmap, vid, add);
        }
    } else {
        rc = EOPNOTSUPP;
    }

    return rc;
}

/* Function to add l3 host entry */
int
ofproto_add_l3_host_entry(struct ofproto *ofproto, void *aux,
                          bool is_ipv6_addr, char *ip_addr,
                          char *next_hop_mac_addr, int *l3_egress_id)
{
    int rc;
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    rc = (s->add_l3_host_entry
            ? s->add_l3_host_entry(ofproto, aux,
                  is_ipv6_addr, ip_addr, next_hop_mac_addr, l3_egress_id)
            : EOPNOTSUPP);

    VLOG_DBG("Add L3 host entry rc=(%d)", rc);

    return rc;
} /* ofproto_add_host_entry */

/* Function to delete l3 host entry */
int
ofproto_delete_l3_host_entry(struct ofproto *ofproto, void *aux,
                             bool is_ipv6_addr, char *ip_addr,
                             int *l3_egress_id)
{
    int rc;
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    rc = (s->delete_l3_host_entry
            ? s->delete_l3_host_entry(ofproto, aux,
                       is_ipv6_addr, ip_addr, l3_egress_id)
            : EOPNOTSUPP);

    VLOG_DBG("Delete L3 host entry rc=(%d)", rc);

    return rc;
} /* ofproto_delete_host_entry */

/* Functionto read and reset host hit bit */
int
ofproto_get_l3_host_hit(struct ofproto *ofproto, void *aux,
                        bool is_ipv6_addr, char *ip_addr,
                        bool *hit_bit)
{
    int rc;
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    rc = s->get_l3_host_hit ?
           s->get_l3_host_hit(ofproto, aux,
           is_ipv6_addr, ip_addr, hit_bit) :
           EOPNOTSUPP;

    VLOG_DBG("L3 host hit-bit rc=(%d)", rc);

    return rc;
} /* ofproto_get_l3_host_hit */

/* Route updates */
int
ofproto_l3_route_action(struct ofproto *ofproto,
                        enum ofproto_route_action action,
                        struct ofproto_route *route)
{
    int rc;
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    rc = s->l3_route_action ?
         s->l3_route_action(ofproto, action, route) :
         EOPNOTSUPP;

    VLOG_DBG("l3_route_action rc=(%d), action %d", rc, action);

    return rc;
}

/* ECMP */
int
ofproto_l3_ecmp_set(struct ofproto *ofproto, bool enable)
{
    int rc;
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    rc = s->l3_ecmp_set ?
         s->l3_ecmp_set(ofproto, enable) :
         EOPNOTSUPP;

    VLOG_DBG("%s rc (%d), enable (%d)", __func__, rc, enable);

    return rc;
}

int
ofproto_l3_ecmp_hash_set(struct ofproto *ofproto, unsigned int hash, bool enable)
{
    int rc;
    struct ops_ofproto_class *s;

    s = CONTAINER_OF(ofproto->ofproto_class, struct ops_ofproto_class, _base);
    rc = s->l3_ecmp_hash_set ?
         s->l3_ecmp_hash_set(ofproto, hash, enable) :
         EOPNOTSUPP;

    VLOG_DBG("%s rc (%d), hash (%x) enable (%d)", __func__, rc, hash, enable);

    return rc;
}
