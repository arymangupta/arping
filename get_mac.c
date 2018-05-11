#include <net/rtsock.h>
#include <jnx/rtslib.h>
#include <jnx/jnx_types.h>
#include <isc/eventlib.h>
#include <jnx/rtslib_ifd_info.h>
#include <net/route.h>
#include <net/if_llc.h>
#include <net/if_atm.h>
#include <net/if_lt.h>
#include <arpa/inet.h>
#include <jnx/rt_table.h>
#include <jnx/junos_util.h>
#include <isc/eventlib.h>
#include <jnx/js_error.h>
u_char src_mac_addr[6];

char*  get_intf_mac (struct sockaddr_dl *sa)
{
        u_char         *cp;
        cp = LLADDR(sa);
       src_mac_addr[0] = cp[0];
        src_mac_addr[1] = cp[1];
       src_mac_addr[2] = cp[2];
        src_mac_addr[3] = cp[3];
        src_mac_addr[4] = cp[4];
        src_mac_addr[5] = cp[5];
	return src_mac_addr;
}

char*  get_mac(char* ifname){
	rtslib_cookie_ptr rtsock_cookie;
	rtsock_cookie = rtslib_open(RTM_ID_UNKNOWN);	
	ifdev_msg_t *ifdm = NULL;
	struct sockaddr_dl *sa;
	rtslib_ifdm_get_by_name(rtsock_cookie, ifname,  RTM_GET, &ifdm, NULL);
	sa = (struct sockaddr_dl *) IFDEV_MSG_ADDR(ifdm);
	return  get_intf_mac(sa);
}
