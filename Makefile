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


#NO_SHARED = yes
.PATH: ${RELSRCTOP}/dist/packetfactory-libnet/src

SRCS +=		\
		libnet_error.c 	\
		libnet_build_icmp.c \
		libnet_build_802.1q.c \
		libnet_build_ethernet.c \
		libnet_write.c \
		libnet_build_arp.c \
		libnet_link_bpf.c \
		libnet_pblock.c \
		libnet_checksum.c \
		libnet_resolve.c \
		libnet_if_addr.c \
		libnet_build_ip.c \
		libnet_raw.c 
							
CFLAGS +=  -I${.CURDIR}/include -I${.CURDIR} -O
DPLIBS =\
	${LIBPCAP} \
	${LIBJXMLUTIL} \
        ${LIBJUNOS-NAME-TREE} \
        ${LIBJUNOS-PATRICIA} \
        ${LIBJUNOS-XMLUTIL} \
        ${LIBJUNOS-PATH} \
        ${LIBUI-ODL} \
        ${LIBISC} \
        ${LIBRTSOCK} \
        ${LIBJUNOS-LOG-TRACE} \
        ${LIBJUNOS-SYS-UTIL} \
        ${LIBM} \
        ${LIBJUNOS-UTIL} \
	${LIBIFINFO}
.include <bsd.prog.mk>
