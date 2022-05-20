void des_cfb_encrypt(unsigned char p[], int n, unsigned char des_seed_iv[], unsigned char des_iv[], unsigned char des_seed_key[])
{
    unsigned char des_key[8], des_vec[8], des_cipher[0x100];
    unsigned int i, j;

    for(i = 0; i < 8; i++)
        des_key[i] = des_seed_key[i] ^ des_iv[i] ^ des_seed_iv[i];

    for(i = 0; i < n; i++){
        for(j = 0; j < 8; j++)
            des_vec[j] = des_iv[j];
        des_encrypt(des_vec, des_key);
        des_cipher[i] = des_vec[0] ^ p[i];
        printf("%02X", des_cipher[i]);
        for(j = 0; j < 8; j++)
            des_iv[j] = des_iv[j + 1];
        des_iv[7] = des_cipher[i];
    }
}