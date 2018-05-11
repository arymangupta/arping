arping/README

 ARP Ping

    By Thomas Habets <thomas@habets.se> modified by Aryaman Gupta <arymangupta331@gmail.com> <aryaman@juniper.net>

 git clone https://github.com/arymangupta/arping.git

Introduction
------------
Arping is a util to find out if a specific IP address on the LAN is 'taken'
and what MAC address owns it. Sure, you *could* just use 'ping' to find out if
it's taken and even if the computer blocks ping (and everything else) you still
get an entry in your ARP cache. But what if you aren't on a routable net? Or
the host blocks ping (all ICMP even)? Then you're screwed. Or you use arping.

Why it's not stupid
-------------------
Say you have a block of N real IANA-assigned IP-addresses. You want to debug
the net and you don't know which IP addresses are taken. You can't ping anyone
before you take the IP, and you can't pick an IP before you know which are
already taken. Catch 22. But with arping you can 'ping' the IP and if you get
no response, the IP is available.

Example uses
------------
If some box is dumping non-IP (like IPX) garbage and you don't know which box
it is, you can ping by MAC to get the IP and fix the problem.

If you are on someone else's net and want to 'borrow' a real IP address instead
of using one of those 10.x.x.x-addresses the DHCP hands out you probably want
to know which ones are taken, or people will get mad (a friend of mine got a
call on his cellphone about 15 seconds after he accidentally 'stole' an IP,
oops).

Compiling / installing
----------------------
Arping is ported fro junos(Juniper Networks operating system) which is FreeBSD based so this code is only meant for junos.
Just do mk in arping directory.
It will only work in Junos!!! 

FAQ
---
Q: Arping can't ping anything!

A: Check which interface is active with -v. If it's the wrong one, use -i
   to set it right.
---
Q: Arping finds some hosts, but not others. why?   BTW, I have several NICs.

A: You have to choose interface with the -i switch if the default is wrong for
   you.
---
Q: I get bus error on my non-x86 box

A: Damn, I thought I fixed those. Tell me how you got it and I'll try to fix
   it. Attaching config.log always helps.
---
Q: I get "libnet_get_ipaddr(): no error" when I run arping with IP (src or dst)
   255.255.255.255.

A: Use the -b/-B switches. Libnet sucks (ha ha only serious) and returns -1 for
   error == int32 encoded 255.255.255.255.
---
Q: I used to be able to use -S 255.255.255.255, now it fails. What's going on?
Q: Why can't I arping 255.255.255.255?

A: Argh! Why would you want to? Anyway, this one is due to libnets resolving,
   and my unwillingness to reimplement it (in a portable manner, ugh).

   -S 255.255.255.255 can be replaced with -b, and pinging broadcast (why you
   would do that eludes me) -B.

   To be extra perverted, try:
   # ./arping -b -B
   (yes, I added -b and -B just so that version 1.0 should be complete)
---
Q: 1.01 is out, didn't you just say 1.0 was supposed to be the last one?

A: Shut up.
---
Q: The roundtrip times are off, sometimes by milliseconds!

A: I know.
   Short answer:
     'ping' does the same thing. (ping from iputils-ss010824 anyway)

   Long answer:
     I can't (portably anyway) do anything other than queue a packet
     to the network. That means I don't know exactly when it arrived. Also,
     I can't tell when a packet arrives on the wire, only when arping gets
     it from the kernel. Just make sure neither the network (whole segment
     if you are hubbed, just your NIC if you are switched) nor your box is
     loaded when you care about timing, and/or run arping with higher
     priority.

     # nice -n -15 arping foobar

     But if you find way to get more exact timing portably (or just for one
     OS really), let me know.
---
Q: Is it OK to make arping suid root?

A: Be my guest, but if care about security *at all* you will have to restrict
   execution of arping to trusted users. I could remove "dangerous" features
   from the code when it's running suid, but I honestly don't want to. This is
   a network debugging tool, which generates low-level network packets that
   ordinary users have absolutely no business generating.

   If you are honestly debugging the network then I don't see why you aren't
   root already.

   That being said, on Linux you can add the CAP_NET_RAW capability to arping
   limiting the damage if arping were to be compromised:
     sudo setcap cap_net_raw+ep  /usr/local/sbin/arping
   This requires a libnet 1.1.5 or higher, which does not explicitly check for
   uid 0.
---
