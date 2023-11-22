#include <stdio.h>

#include <errno.h>
#include <netdb.h>
#include <nss.h>
#include <string.h>
#include <threads.h>

thread_local int reentered = 0;

enum nss_status _nss_dns_gethostbyname4_r(
        const char *name, struct gaih_addrtuple **pat,
        char *buffer, size_t buflen, int *errnop,
        int *herrnop, int32_t *ttlp);

enum nss_status
_nss_netdependent_gethostbyname4_r(const char *name,
                                   struct gaih_addrtuple **pat, char *buffer,
                                   size_t buflen, int *errnop, int *herrnop,
                                   int32_t *ttlp)
{
    fprintf(stderr, "NSS NETDEPENDENT: Called %s with args (name: %s)\n",
            __FUNCTION__, name);

    if (reentered) {
        *errnop = ENOENT;
        fprintf(stderr, "reentered abort\n");
        return NSS_STATUS_UNAVAIL;
    }
    reentered = 1;
    fprintf(stderr, "non-reentered proceed\n");

    ///

    struct hostent result;

    enum nss_status status = NSS_STATUS_UNAVAIL;
    if (strcmp(name, "abcd") == 0) {
        fprintf(stderr, "abcd\n");
        char* lookupname = "google.com";
        status = _nss_dns_gethostbyname4_r(
            lookupname, pat, buffer, buflen, errnop, herrnop, ttlp);
        reentered = 0;
        return status;
    }

    fprintf(stderr, "not abcd\n");
    reentered = 0;
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
}

enum nss_status
_nss_netdependent_gethostbyname2_r(const char *name, int af,
                                   struct hostent *host, char *buffer,
                                   size_t buflen, int *errnop, int *h_errnop)
{
    fprintf(stderr, "NSS NETDEPENDENT: Called %s with args (name: %s)\n",
            __FUNCTION__, name);
    if (reentered) {
        *errnop = ENOENT;
        fprintf(stderr, "reentered abort\n");
        return NSS_STATUS_UNAVAIL;
    }
    reentered = 1;
    fprintf(stderr, "non-reentered proceed\n");

    ///

    struct hostent result;

    enum nss_status status = NSS_STATUS_UNAVAIL;
    if (strcmp(name, "abcd") == 0) {
        fprintf(stderr, "abcd\n");
        char* lookupname = "yahoo.de";
        status = _nss_dns_gethostbyname2_r(lookupname, af, host, buffer,
                                           buflen, errnop, h_errnop);
        reentered = 0;
        return status;
    }

    fprintf(stderr, "not abcd\n");
    reentered = 0;
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
}
