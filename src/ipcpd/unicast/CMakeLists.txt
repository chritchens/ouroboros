get_filename_component(CURRENT_SOURCE_PARENT_DIR
  ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(CURRENT_BINARY_PARENT_DIR
  ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CURRENT_SOURCE_PARENT_DIR})
include_directories(${CURRENT_BINARY_PARENT_DIR})

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include)

set(IPCP_UNICAST_TARGET ipcpd-unicast CACHE INTERNAL "")

protobuf_generate_c(KAD_PROTO_SRCS KAD_PROTO_HDRS kademlia.proto)

math(EXPR PFT_EXPR "1 << 12")
set(PFT_SIZE ${PFT_EXPR} CACHE STRING
  "Size of the PDU forwarding table")
if (HAVE_FUSE)
  set(IPCP_FLOW_STATS TRUE CACHE BOOL
    "Enable flow statistics tracking in IPCP")
    if (IPCP_FLOW_STATS)
       message(STATUS "IPCP flow statistics enabled")
    else ()
       message(STATUS "IPCP flow statistics disabled")
    endif ()
endif ()


set(SOURCE_FILES
  # Add source files here
  addr_auth.c
  connmgr.c
  dht.c
  dir.c
  dt.c
  enroll.c
  fa.c
  main.c
  pff.c
  routing.c
  psched.c
  # Add policies last
  pol/alternate_pff.c
  pol/flat.c
  pol/link_state.c
  pol/graph.c
  pol/simple_pff.c
  )

add_executable(ipcpd-unicast ${SOURCE_FILES} ${IPCP_SOURCES}
  ${KAD_PROTO_SRCS} ${LAYER_CONFIG_PROTO_SRCS})
target_link_libraries(ipcpd-unicast LINK_PUBLIC ouroboros-dev)

include(AddCompileFlags)
if (CMAKE_BUILD_TYPE MATCHES "Debug*")
  add_compile_flags(ipcpd-unicast -DCONFIG_OUROBOROS_DEBUG)
endif ()

install(TARGETS ipcpd-unicast RUNTIME DESTINATION ${CMAKE_INSTALL_SBINDIR})

add_subdirectory(pol/tests)

if (NOT GNU)
  add_subdirectory(tests)
endif ()
