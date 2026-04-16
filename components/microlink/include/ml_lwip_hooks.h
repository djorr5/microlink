#pragma once

/*
 * Rename ESP-IDF's default IPv4 source-route hook so Microlink can wrap it
 * and force tailnet traffic onto the WireGuard netif.
 */
#define ip4_route_src_hook microlink_default_ip4_route_src_hook
