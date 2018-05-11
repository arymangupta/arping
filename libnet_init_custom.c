#if (HAVE_CONFIG_H)
#include "../include/config.h"
#endif
#if (!(_WIN32) || (__CYGWIN__)) 
#include "../include/libnet.h"
#else
#include "../include/win32/libnet.h"
#endif

libnet_t *
libnet_init(int injection_type, char *device, char *err_buf)
{
    libnet_t *l = NULL;

#if 0 /* JUNOS - ignore this code */
#if !defined(__WIN32__)
    if (getuid() && geteuid())
    {
        snprintf(err_buf, LIBNET_ERRBUF_SIZE,
                "%s(): UID or EUID of 0 required\n", __func__);
        goto bad;
    }
#else
    WSADATA wsaData;

    if ((WSAStartup(0x0202, &wsaData)) != 0)
    {
        snprintf(err_buf, LIBNET_ERRBUF_SIZE, 
                "%s(): unable to initialize winsock 2\n", __func__);
        goto bad;
    }
#endif
#endif /* JUNOS - end of ignored code */

    l = (libnet_t *)malloc(sizeof (libnet_t));
    if (l == NULL)
    {
#if 0 /*JUNOS - ignore this code */
        snprintf(err_buf, LIBNET_ERRBUF_SIZE, "%s(): malloc(): %s\n", __func__,
                strerror(errno));
#endif /* JUNOS - end of ignored code */

        goto bad;
    }
	
    memset(l, 0, sizeof (*l));

    l->injection_type   = injection_type;
    l->ptag_state       = LIBNET_PTAG_INITIALIZER;
    l->device           = (device ? strdup(device) : NULL);

    strncpy(l->label, LIBNET_LABEL_DEFAULT, LIBNET_LABEL_SIZE);
    l->label[sizeof(l->label)-1] = '\0';
    switch (l->injection_type)
    {
        case LIBNET_LINK:
        case LIBNET_LINK_ADV:
            if (libnet_select_device(l) == -1)
            {
                snprintf(err_buf, LIBNET_ERRBUF_SIZE, l->err_buf);
		goto bad;
            }
            if (libnet_open_link(l) == -1)
            {
                snprintf(err_buf, LIBNET_ERRBUF_SIZE, l->err_buf);
                goto bad;
            }
            break;
        case LIBNET_RAW4:
        case LIBNET_RAW4_ADV:
            if (libnet_open_raw4(l) == -1)
            {
                snprintf(err_buf, LIBNET_ERRBUF_SIZE, l->err_buf);
                goto bad;
            }
            break;
        case LIBNET_RAW6:
        case LIBNET_RAW6_ADV:
            if (libnet_open_raw6(l) == -1)
            {
                snprintf(err_buf, LIBNET_ERRBUF_SIZE, l->err_buf);
                goto bad;
            }
            break;
        default:
            snprintf(err_buf, LIBNET_ERRBUF_SIZE,
                    "%s(): unsupported injection type\n", __func__);
            goto bad;
            break;
    }

    return (l);

bad:
    if (l)
    {
        libnet_destroy(l);
    }
    return (NULL);
}

void
libnet_destroy(libnet_t *l)
{
    if (l)
    {
        close(l->fd);
        if (l->device)
        {
            free(l->device);
        }
        libnet_clear_packet(l);

        free(l);
    }
}

void
libnet_clear_packet(libnet_t *l)
{
    libnet_pblock_t *p;
    libnet_pblock_t *next;

    if (l)
    {
        p = l->protocol_blocks;
        if (p)
        {
            for (; p; p = next)
            {
                next = p->next;
                if (p->buf)
                {
                    free(p->buf);
                }
                free(p);
            }
        }
        l->protocol_blocks = NULL;
        l->total_size = 0;
    }
}
