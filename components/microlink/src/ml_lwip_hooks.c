#include "lwip_default_hooks.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"

#undef ip4_route_src_hook

static struct netif *s_microlink_wg_netif = NULL;

bool ml_lwip_hooks_active(void)
{
    return true;
}

void ml_lwip_set_wg_netif(struct netif *netif)
{
    s_microlink_wg_netif = netif;
}

struct netif *ip4_route_src_hook(const ip4_addr_t *src, const ip4_addr_t *dest)
{
    if (dest != NULL && s_microlink_wg_netif != NULL &&
        netif_is_up(s_microlink_wg_netif) &&
        netif_is_link_up(s_microlink_wg_netif) &&
        !ip4_addr_isany_val(*netif_ip4_addr(s_microlink_wg_netif)) &&
        ip4_addr_netcmp(dest,
                        netif_ip4_addr(s_microlink_wg_netif),
                        netif_ip4_netmask(s_microlink_wg_netif))) {
        return s_microlink_wg_netif;
    }

    return microlink_default_ip4_route_src_hook(src, dest);
}
