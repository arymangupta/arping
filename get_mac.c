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
#include <string.h>
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

/*
 * @brief
 * Given an ifindex, return its underlying device name.
 *
 * @param[in] ifindex
 *      an iflindex number 
 * 
 * @param[out] name
 * 	name of the underlying device
 *
 * @param[out] size of the storage for the device name
 *      The ifl device name.
 */
int
ifl_get_device_byifindex(int  ifindex)
{
    rtslib_cookie_ptr  cookie = NULL;
    ifl_msg_t*         iflm = NULL;
    ifl_msg_map_t*     iflm_map = NULL;
    ifl_idx_t          idx;
	idx.x = ifindex;
    int                error;

    cookie = rtslib_open(RTM_ID_UNKNOWN);
    if (!cookie) {
        return -1;
    }

    /* Loop till we hit bottom of the ifl stack */
    while (ifl_idx_t_getval(idx)) {
        error = rtslib_iflm_get_by_index(cookie, idx, RTM_GET, &iflm,
                                         &iflm_map);
        if (error) {
            rtslib_close(cookie);
            return -1;
        }
        if (iflm == NULL) {
            return -1;
        }

        idx = iflm->iflm_underlying_index;
        if (ifl_idx_t_getval(idx) == 0) {
	  printf("name %s\n" , IFL_MSG_NAME(iflm) ); //DEBUG
        }

        RTSLIB_MSG_FREE(cookie, iflm, iflm_map);
    }

    rtslib_close(cookie);

    return 0;
}

void handle_IRB(char* ifname)
{
}
char*  get_mac(char* ifname){
	rtslib_cookie_ptr rtsock_cookie;
	rtsock_cookie = rtslib_open(RTM_ID_UNKNOWN);
	if(!rtsock_cookie) printf("ERRORINCOOKIE \n");	
	ifdev_msg_t *ifdm = NULL;
	struct sockaddr_dl *sa;
	
	ifl_msg_t *iflm = NULL;
	ifl_msg_map_t *iflm_map = NULL;
	char                dev[IFNAMELEN];
	if_subunit_t        subunit;
	if(strstr(ifname , "irb.") || strstr(ifname, "."))
	{
		printf("%d \n" , ifl_getindexbyifname(ifname));
		if(ifl_get_device_name(ifname, dev, IFNAMELEN, &subunit) < 0) printf("ERROR\n");
		if(rtslib_iflm_get_by_name(rtsock_cookie, dev, subunit, RTM_GET, &iflm,  &iflm_map)>0) printf("ERROR\n");
		vlan_msg_t *vlanm = NULL;
		int  ifindex = ifl_idx_t_getval(iflm->iflm_index);
		char buff[100];
		ifl_get_device_byifindex(ifindex);
		//int vlan_id = rtslib_vlanm_get_by_l3ifl(rtsock_cookie , iflm->iflm_index , RTM_GET , &vlanm);
	}
	else
	{
	rtslib_ifdm_get_by_name(rtsock_cookie, ifname,  RTM_GET, &ifdm, NULL);
	sa = (struct sockaddr_dl *) IFDEV_MSG_ADDR(ifdm);      
	return  get_intf_mac(sa);
	}
	rtslib_ifdm_get_by_name(rtsock_cookie, dev,  RTM_GET, &ifdm, NULL);
	sa = (struct sockaddr_dl *) IFDEV_MSG_ADDR(ifdm);
	return  get_intf_mac(sa);
}
