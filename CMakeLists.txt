# (c) Copyright 2015 Hewlett Packard Enterprise Development LP
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.

set (LIB_DIR lib)
set (OFPROTO_DIR ofproto)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I$(OVS_INCLUDE) -std=gnu99 -Werror")
set (SOURCES_LIB ${LIB_DIR}/ops-netdev.h
                 ${LIB_DIR}/ops-netdev.c
                 ${LIB_DIR}/ops-netdev-provider.h)
add_library (opsopenvswitch ${SOURCES_LIB})
install (TARGETS opsopenvswitch ARCHIVE DESTINATION lib)
