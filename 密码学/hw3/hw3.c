void build_sbox_inverse(void)
{
	int i;
    unsigned char row, col;
	for(i = 0; i < 256; i++){
        sbox_inverse[sbox[i]] = i;
	}
}

void aes_polynomial_mul(unsigned char x[4], unsigned char y[4], unsigned char z[4])
{
	int i, j, k;
    unsigned char t[4];
	for(i = 0, k = 4; i < 4; i++, k--){
		t[3-i] = 0;
		for(j = 0; j < 4; j++){
			t[3-i] ^= aes_8bit_mul_mod_0x11B(x[j], y[(k+j)&3]);
		}
	}
    memcpy(z, t, 4);
}

void ByteSubInverse(unsigned char *p, int n)
{
	int i;
	for(i = 0; i < n; i++){
		p[i] = sbox_inverse[p[i]];
	}
}

void ShiftRowInverse(unsigned char *p)
{
	int i;
	for(i = 1; i < 4; i++){
		ror_a_row(p + i * 4, i);
	}
}

void MixColumnInverse(unsigned char *p, unsigned char a[4], int do_mul)
{
	unsigned char b[4];
    unsigned char t[4][4];
    int j;
    for(j = 0; j < 4; j++) {
        memcpy(b, p+4*j, 4);
        
        if(do_mul){
            aes_polynomial_mul(a, b, b); /* 其余轮都要做乘法: b = a*b mod (X^4+1); */
        }
      put_column(b, t, j); /* 把乘法所得结果复制到t中第j行 */
   }
   memcpy(p, t, 4*4);
}

void aes_decrypt(unsigned char *bufin, unsigned char *bufout, unsigned char *key)
{
    int i;
   unsigned char a[4] = {0xB, 0xD, 0x9, 0xE}; /* 定义多项式3*X^3+X^2+X+2 */
   unsigned char matrix[4][4];
   memcpy(matrix, bufin, 4*4); /* 复制明文16字节到matrix */
    
    /* 第0轮只做AddRoundKey() */
   for(i=key_rounds; i>0; i--)
   {  /* 第1至key_rounds轮, 做以下步骤: AddRoundKey, ByteSub, ShiftRow, MixColumn*/
      AddRoundKey((unsigned char *)matrix, key+i*(4*4));
      if(i != key_rounds)
         MixColumnInverse((unsigned char *)matrix, a, 1); /* do mul */
      else
         MixColumnInverse((unsigned char *)matrix, a, 0); /* don't mul */
       ShiftRowInverse((unsigned char *)matrix);
       MixColumn((unsigned char *)matrix, a, 0); /* 不做乘法, 只做矩阵行转列 */
       ByteSubInverse((unsigned char *)matrix, 16);
   }
    AddRoundKey((unsigned char *)matrix, key);
   memcpy(bufout, matrix, 4*4); /* 密文复制到bufout */
}