static void perm_init(char perm[8][256][8], char p[64]) /* 64-bit, either init or final */
{
   register int b, j, k;
   int i;

    /* Clear the permutation array */
    memset(perm, 0, 8 * 256 * 8);
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 256; j++) {
            for(k = 0; k < 64; k++){
                b = p[k] - 1;
                if((b >> 3 == i) && (j & bytebit[b & 7])){
                    perm[i][j][k >> 3] |= bytebit[k & 7];
                } 
            }
        }
    }
}

static void permute(char *inblock, char perm[8][256][8], char *outblock)
{   /* result into outblock, 64 bits */
    register int i, j;
    register char *pin, *pout, *p;
    
    if(perm == NULL){
        /* No permutation, just copy */
        memcpy(outblock, inblock, 8);
        return;
    }

     /* Clear output block    */
    memset(outblock, 0, 8);
    pin = inblock;
    for(j = 0; j < 8; j++){
        pout = outblock;
        p = perm[j][(unsigned char)*pin++];
        for(i = 0; i < 8; i++) /* and each output byte */
            *pout++ |= *p++;
   }
}

int des_init(int mode)
{
   if(sbox_output_perm_table != NULL)
   {
      /* Already initialized */
      return 1;
   }
   des_mode = mode;
   
   if((sbox_output_perm_table = (long32 (*)[64])malloc(sizeof(long32) * 8 * 64)) == NULL)
   {
      return 0;
   }
   sbox_output_perm_table_init();
   kn = (unsigned char (*)[8])malloc(sizeof(char) * 16 * 8);
   if(kn == NULL)
   {
      free((char *)sbox_output_perm_table);
      return 0;
   }
   if(mode == 1 || mode == 2)   /* No permutations */
      return 1;

   iperm = (char (*)[256][8])malloc(sizeof(char) * 8 * 256 * 8); //change to 256
   if(iperm == NULL)
   {
      free((char *)sbox_output_perm_table);
      free((char *)kn);
      return 0;
   }
   perm_init(iperm, ip);

   fperm = (char (*)[256][8])malloc(sizeof(char) * 8 * 256 * 8); //change to 256
   if(fperm == NULL)
   {
      free((char *)sbox_output_perm_table);
      free((char *)kn);
      free((char *)iperm);
      return 0;
   }
   perm_init(fperm, fp);   
   return 1;
}