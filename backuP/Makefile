#	@(#)Makefile	8.1 (Berkeley) 6/5/93
# $FreeBSD: src/sbin/arping/Makefile,v 1.12.2.4 2001/12/19 04:49:11 dd Exp $

PROG =	arping
SRCS =  arping_main.c \
        arping.c \
        unix.c \
        findif_getifaddrs.c \
        get_mac.c \
	libnet_init_custom.c

BINOWN= root
BINMODE=4555


SRCS +=	${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_error.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_build_icmp.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_build_802.1q.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_build_ethernet.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_write.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_build_arp.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_link_bpf.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_pblock.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_checksum.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_resolve.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_if_addr.c \
		${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_build_ip.c \
		 ${SB_JUNOS}/src/dist/packetfactory-libnet/src/libnet_raw.c 
							
INCLUDE_DIR = -I${SB_JUNOS}/src/junos/bsd/sbin/arping/include -I${SB_JUNOS}/src/junos/bsd/sbin/arping
CFLAGS += ${INCLUDE_DIR} 
DPLIBS = ${LIBPCAP} \
        ${LIBJXMLUTIL} \
        ${LIBJUNOS-NAME-TREE} \
        ${LIBJUNOS-PATRICIA} \
        ${LIBJUNOS-XMLUTIL} \
        ${LIBJUNOS-PATH} \
        ${LIBUI-ODL} \
        ${LIBISC} \
        ${LIBRTSOCK} \
	${LIBJUNOS-PARSE} \
        ${LIBJUNOS-UI-UTIL} \
        ${LIBJUNOS-INTERFACE-UTIL} \
        ${LIBJUNOS-LOG-TRACE} \
        ${LIBJUNOS-STRING} \
        ${LIBJUNOS-CHECKSUM} \
        ${LIBJUNOS-LOG-TRACE} \
        ${LIBJUNOS-SYS-UTIL} \
        ${LIBM} \
        ${LIBJUNOS-UTIL} \
	${LIBJUNOS-PRODUCT-INFO} \
        ${LIBPVIDB} \
        ${LIBJUNOS-TNPHOST}

.include <bsd.prog.mk>
