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

#ifndef OPS_NETDEV_H
#define OPS_NETDEV_H 1

#include "netdev.h"

#ifdef  __cplusplus
extern "C" {
#endif

int netdev_set_hw_intf_info(struct netdev *, const struct smap *args);
int netdev_set_hw_intf_config(struct netdev *, const struct smap *args);

#ifdef  __cplusplus
}
#endif

#endif /* ops-netdev.h */
