static long32 f(ulong32 r, unsigned char subkey[8]) 
{
    unsigned char s[4], plaintext[8], m[4], t[4];
    unsigned long int rval;
    unsigned char *uchar_ptr;
    int i, j;
    unsigned char bit_index;

    memset(plaintext, 0, sizeof(plaintext));
    memset(m, 0, sizeof(m));
    memset(t, 0, sizeof(t));

    //step 1
    uchar_ptr = (unsigned char *)&r;
    for(i = 3; i >= 0; i--){
        s[i] = *uchar_ptr;
        uchar_ptr++;
    }

    //step 2
    for(i = 0; i < 8; i++){
        for(j = 0; j < 6; j++){
            bit_index = plaintext_32bit_expanded_to_48bit_table[6 * i + j] - 1;
            plaintext[i] |= ((s[bit_index >> 3] & bytebit[bit_index & 7]) != 0) << (5 - j);
        }
    }

    //step 3
    for(i = 0; i < 8; i++)
        plaintext[i] ^= subkey[i];

    //step 4
    for(i = 0; i < 8; i++){
        bit_index = (plaintext[i] & 0x20) | ((plaintext[i] & 0x1) << 4) + ((plaintext[i] & 0x1E) >> 1);
        m[i / 2] |= (sbox[i][bit_index] << ((i % 2) ? 0 : 4));
    }

    //step 5
    for(i = 0; i < 32; i++){
        bit_index = sbox_perm_table[i] - 1;
        t[i >> 3] |= ((m[bit_index >> 3] & bytebit[bit_index & 7]) != 0) << (7 - i%8);
    }

    //step 6
    uchar_ptr = (unsigned char *)&rval;
    for(i = 3; i >= 0; i--){
        *uchar_ptr = t[i];
        uchar_ptr++;
    }

    return rval;

}