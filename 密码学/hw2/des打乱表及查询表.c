
int ip[64]={58, ...}; // 16轮循环前的打乱表
ip[0] == 58; // 目标位号(下标)=0, 源位号(元素值)=58-1=57
;
16轮循环
;
int fp[64]={...}; // 16轮循环后的打乱表
其中fp[57] == 1; 源位号(下标)=57, 目标位号(元素值)=1-1=0


//用循环法把源数组s中的64位打乱并保存到目标数组t
char s[8], t[8], ip[64]={...};
int i, j, byte, bit;
unsigned char mask[8]={0x80, 0x40, 0x20, 0x10, 8, 4, 2, 1};
memset(t, 0, sizeof(t));
for(i=0; i<64; i++) // i=目标位号(base 0)
{
   n = ip[i] - 1; // n=源位号, ip[i]是以1为基数的源位号
   byte = n >> 3; // n / 8; // 第n位位于s中第byte字节
   bit = n & 7; // n % 8; // 第n位位于byte字节中的第bit位
   if(s[byte] & mask[bit]) // if(s[byte] &  1<<(7-bit))
      t[i/8] |= mask[i%8]; // 目标第n位置1
}

//permute() 
//通过查询table把源数组s中的64位打乱并保存到目标数组t
unsigned char table[16][16][8]={...};
unsigned char s[8], t[8], B4, *p;
int i, j, k;
memset(t, 0, sizeof(t));
for(i=0; i<16; i++) // i=源数据组号, 每4位一组
{//组号   0     1      2      3    ...   14     15
 //      s[0]  s[0]   s[1]   s[1]       s[7]   s[7]
 //      高4位 低4位  高4位  低4位      高4位  低4位
   B4 = (s[i/2] >> i%2==0?4:0) & 0x0F; // B4=第i组的4位值
   p = table[i][B4]; // p->8字节数组的首字节, 这8字节中仅
   for(k=0; k<8; k++)// 有4个位是目标位, 其余60位均为0
      t[k] |= p[k];  // 把4个目标位保存到t中; 因为不确定
                     // 这4个位分布在8个字节中的何处, 故
                     // 把8字节全部与目标数组t做或运算;
}


//如何根据打乱表如int ip[64]生成
//查询表table[16][16][8]?
//perm_init()
unsigned char mask[4]={8, 4, 2, 1};
memset(table, 0, sizeof(table));
for(i=0; i<16; i++) // 组号
{
   for(B4=0; B4<16; B4++) // 第i组4位的值
   {
      for(k=0; k<4; k++) // B4中的第k位
      {
         if((B4 & mask[k]) == 0) // if(B4 & 1<<(3-k)), B4的第k位==0
            continue;
         /* 若只允许查ip打乱表, 则通过j循环找到源位号n
         for(j=0; j<64; j++) // j=目标位号
         {
            if(ip[j]-1 == i*4+k) // 若ip中保存的源位号跟当前源位号相等
               break;
         }
         n = j;
         */
         n = fp[i*4+k]-1; // 源位号=i*4+k, n=目标位
         table[i][B4][n/8] |= 1<<(7-n%8); // 把第n位置1
      }
   }
}
