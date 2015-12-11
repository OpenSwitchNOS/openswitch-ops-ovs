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

#ifndef OPS_NETDEV_PROVIDER_H
#define OPS_NETDEV_PROVIDER_H 1

#include "netdev-provider.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct ops_netdev {
    struct netdev _base;
    struct shash_node *refd_node;  /* Pointer to element in netdev_refd map */
};

struct ops_netdev_class {
    struct netdev_class _base;

    /* Sets the device 'netdev''s hw_intf_info to 'args'.
     *
     * If this netdev class does not support hardware info, this may be a null
     * pointer. */
    int (*set_hw_intf_info)(struct netdev *netdev, const struct smap *args);

    /* Changes the device 'netdev''s hw_intf_config to 'args'.
     *
     * If this netdev class does not support hardware configuration,
     * this may be a null pointer. */
    int (*set_hw_intf_config)(struct netdev *netdev, const struct smap *args);
};

#ifdef  __cplusplus
}
#endif

#endif /* ops-netdev-provider.h */
