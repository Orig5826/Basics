
#include "demo.h"

int main()
{
    #if 0
    sha1_demo();
    sha256_demo();
    sha512_demo();
    aes_demo();
    aes_cbc_demo();
    ecdh_demo();
    ecdsa_demo();
    #endif

    des_demo();
    des_cbc_demo();

    return 0;
}