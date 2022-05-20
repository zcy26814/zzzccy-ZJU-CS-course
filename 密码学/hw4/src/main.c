#include <stdio.h>
#include <time.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/sha.h>
char A[0x100], B[0x100], PE[0x100];   // ecc曲线参数a, b, p
char GX[0x100], GY[0x100], NE[0x100]; // 基点G的x坐标, y坐标, G的阶(均为256位)
char DE[0x100];                       // ecc的私钥d(256位)
char N1[2][0x100], D1[2][0x100], X2[2][0x100]; 
                // N1存放用ecc公钥加密过的rsa参数N, 
                // 其中N1[0]存放第1部分密文, N1[1]存放第2部分密文;
                // D1存放用ecc公钥加密过的rsa私钥d;
                // X2存放用ecc公钥加密过的X1
char X1[0x100]; // X1存放用rsa公钥加密过的X                      
char X[0x100];  // X存放一个256位的随机数, X<N 且 X<NE
char N[0x100], D[0x100];       // rsa的N及私钥d(256位)
char RX[0x100], RY[0x100];     // ecc公钥R的x坐标及y坐标 
char C[2][0x100]; // 存放用ecc公钥加密过的X, C[0]是第1部分密文, C[1]是第2部分密文
char S[2][0x100]; // 存放用ecnr签名过的RSA_private_encrypt_PKCS1_type_2(SHA1(X), D)
                  // 其中SHA1是散列算法, RSA_private_encrypt_PKCS1_type_2()是用RSA的
                  // 私钥d对SHA1(X)进行加密(实际上是签名), 加密前必须对SHA1(X)按PKCS1_type_2
                  // 方式进行填充, 使得SHA1(X)的长度从20字节变成0x20字节(即256位);
                  // 针对N为256位的PKCS1_type_2填充格式如下:
                  // 0x00, 0x02, 9字节非零随机数, 0x00, 20字节明文
                  // 归纳起来讲, S是对SHA1(X)的两次签名, 第1次是用rsa的私钥签名, 第2次是用ecc的私钥签名

int main()
{
	//ecc相关参数定义
	EC_GROUP *group;
	BN_CTX *ctx;
	EC_POINT *G, *T=NULL, *R;
	BIGNUM *p, *a, *b, *ne, *gx, *gy, *tx, *ty;
	BIGNUM *m, *d, *k, *r, *s;
	//RSA相关参数定义
	RSA *prsa;
	BIGNUM *pn, *pe, *pd;
	//循环以及随机种子的相关变量
	int i, n;
	time_t c_time;
	//Xi是X1的bn，但实际上没用到；X_bin是X的十六进制字符串，X_SHA是X_bin的SHA加密后的摘要；
	//X_SHA_P是X_SHA填充后得到的32位字符串，X_SHA_C是X_SHA_P在RSA加密后的密文
	unsigned char Xi[0x100], X_bin[0x100], X_SHA[0x100], X_SHA_P[0x100], X_SHA_C[0x100];


	//先输入各个参数变量，以及参数的创建
	scanf("%s", A);
	scanf("%s", B);
	scanf("%s", PE);
	scanf("%s", GX);
	scanf("%s", GY);
	scanf("%s", NE);
	scanf("%s", DE);
	scanf("%s", N1[0]);
	scanf("%s", N1[1]);
	scanf("%s", D1[0]);
	scanf("%s", D1[1]);
	scanf("%s", X2[0]);
	scanf("%s", X2[1]);

	p = BN_new();
	a = BN_new();
	b = BN_new();
	ne = BN_new();
	gx = BN_new();
	gy = BN_new();
	tx = BN_new();
	ty = BN_new();
	m = BN_new();
	d = BN_new();
	k = BN_new();
	r = BN_new();
	s = BN_new();

	//配置椭圆曲线的相关参数
	BN_hex2bn(&a, A);
	BN_hex2bn(&b, B);
	BN_hex2bn(&p, PE);
	BN_hex2bn(&ne, NE);
	BN_hex2bn(&gx, GX);
	BN_hex2bn(&gy, GY);
	BN_hex2bn(&d, DE);

	group = EC_GROUP_new(EC_GFp_mont_method());
	ctx = BN_CTX_new();
	EC_GROUP_set_curve_GFp(group, p, a, b, ctx);
	G = EC_POINT_new(group);
	EC_POINT_set_affine_coordinates_GFp(group, G, gx, gy, ctx);
//	if(!EC_POINT_is_on_curve(group, G, ctx)) {
//		puts("G is not one the curve");
//		goto ...;
//	}
	EC_GROUP_set_generator(group, G, ne, BN_value_one());
//	dump_ecc(group);

	//T是椭圆曲线上的一个临时点
	T = EC_POINT_new(group);

	//接下来三段代码形式相同，分别对N1,D1,X2进行解密
	BN_hex2bn(&r, N1[0]);
	BN_hex2bn(&s, N1[1]);
	EC_POINT_set_compressed_coordinates_GFp(group, T, r, 0, ctx);
	EC_POINT_mul(group, T, NULL, T, d, ctx);
	EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx);
	BN_mod_inverse(tx, tx, ne, ctx);
	BN_clear(m);
	BN_mod_mul(m, s, tx, ne, ctx);
	memset(N, 0, sizeof(N));
	strcpy(N, BN_bn2hex(m));

	BN_hex2bn(&r, D1[0]);
	BN_hex2bn(&s, D1[1]);
	EC_POINT_set_compressed_coordinates_GFp(group, T, r, 0, ctx);
	EC_POINT_mul(group, T, NULL, T, d, ctx);
	EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx);
	BN_mod_inverse(tx, tx, ne, ctx);
	BN_clear(m);
	BN_mod_mul(m, s, tx, ne, ctx);
	memset(D, 0, sizeof(D));
	strcpy(D, BN_bn2hex(m));
		
	BN_hex2bn(&r, X2[0]);
	BN_hex2bn(&s, X2[1]);
	EC_POINT_set_compressed_coordinates_GFp(group, T, r, 0, ctx);
	EC_POINT_mul(group, T, NULL, T, d, ctx);
	EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx);
	BN_mod_inverse(tx, tx, ne, ctx);
	BN_clear(m);
	BN_mod_mul(m, s, tx, ne, ctx);
	memset(X1, 0, sizeof(X1));
	strcpy(X1, BN_bn2hex(m));
//	memset(Xi, 0, sizeof(Xi));
//	BN_bn2bin(m, Xi);
	
	//配置RSA的相关参数
	prsa = RSA_new();
	pn = BN_new();
	pe = BN_new();
	pd = BN_new();
	BN_hex2bn(&pn, N);
	BN_hex2bn(&pd, D);

	//在rsa.h 1.0版本前允许直接访问成员变量，但1.1之后版本用RSA_set0_key来对prsa赋值
	prsa->n = pn;
	prsa->e = NULL;
	prsa->d = pd;
//	RSA_set0_key(prsa, pn, NULL, pd);
//	RSA_set_flags(prsa, RSA_FLAG_NO_BLINDING);
	
	//由于不知道为什么直接调用RSA_private_decrypt会出现异常，所以这里直接用BN_mod_exp替代解密过程
//	n = strlen(X1)/2;
	memset(X, 0, sizeof(X));
	BN_mod_exp(m, m, pd, pn, ctx);
	strcpy(X, BN_bn2hex(m));
//	RSA_private_decrypt(n, Xi, X, prsa, RSA_NO_PADDING);
	
	//对X用ecc加密
	R = EC_POINT_new(group);
	EC_POINT_mul(group, R, d, NULL, NULL, ctx);
	EC_POINT_get_affine_coordinates_GFp(group, R, tx, ty, ctx);
	memset(RX, 0, sizeof(RX));
	strcpy(RX, BN_bn2hex(tx));

	c_time = (time_t)time(NULL);
	RAND_add(&c_time, sizeof(c_time), 1);
	BN_rand(k, BN_num_bits(ne), 0, 0);


	EC_POINT_mul(group, T, k, NULL, NULL, ctx);
	EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx);
	memset(C[0], 0, sizeof(C[0]));
	strcpy(C[0], BN_bn2hex(tx));

	BN_hex2bn(&m, X);
	EC_POINT_mul(group, T, NULL, R, k, ctx);
	EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx);
	BN_mod_mul(ty, m, tx, ne, ctx);;
	memset(C[1], 0, sizeof(C[1]));
	strcpy(C[1], BN_bn2hex(ty));

	//对X用SHA1加密，获取摘要；
	//这里由于X是固定长度为32个HEX字符，即64字节，所以可以不用n
/*
	n = strlen(X)/2;
	for(i = 0; i < n; i++){
		sscanf((char *)&X[i*2], "%02X", &X_bin);
	}
	SHA1(X_bin, n, X_SHA);
	RSA_padding_add_PKCS1_type_2(p, n, X_SHA, 20);
*/
	//先获得X的bin表示，放在X_bin中
	memset(X_bin, 0, sizeof(X_bin));
	for(i = 0; i < 32; i++){
		sscanf((char *)&X[i*2], "%02X", &X_bin[i]);
	}
	memset(X_SHA, 0, sizeof(X_SHA));
	SHA1(X_bin, 32, X_SHA);
	memset(X_SHA_P, 0, sizeof(X_SHA_P));
	//按照PKCS1_type_2格式padding X_SHA_P
	RSA_padding_add_PKCS1_type_2(X_SHA_P, 32, X_SHA, 20);
	//这里调用RSA_private_encrypt也出现了异常，所以用BN_mod_exp代替实现
	memset(X_SHA_C, 0, sizeof(X_SHA_C));
	BN_bin2bn(X_SHA_P, 32, m);
	BN_mod_exp(m, m, pd, pn, ctx);
	strcpy(X_SHA_C, BN_bn2hex(m));
//	RSA_private_encrypt(32, X_SHA_P, X_SHA_C, prsa, RSA_NO_PADDING);

	//用ecnr对RSA加密后SHA(X)的进行签名

	//得到随机数
	c_time = (time_t)time(NULL);
	RAND_add(&c_time, sizeof(c_time), 1);
	BN_rand(k, BN_num_bits(ne), 0, 0);

	BN_hex2bn(&m, X_SHA_C);
	//r = k*G+m
	EC_POINT_mul(group, T, k, NULL, NULL, ctx);
	EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx);
	BN_mod_add(ty, tx, m, ne, ctx);
	memset(S[0], 0, sizeof(S[0]));
	strcpy(S[0], BN_bn2hex(ty));

	//s = k-r*d
	BN_mod_mul(tx, ty, d, ne, ctx);
	BN_set_negative(tx, 1);
	BN_mod_add(ty, k, tx, ne, ctx);
	memset(S[1], 0, sizeof(S[1]));
	strcpy(S[1], BN_bn2hex(ty));

	//释放内存
	BN_free(a);
	BN_free(b);
	BN_free(p);
	BN_free(ne);
	BN_free(gx);
	BN_free(gy);
	BN_free(d);
	BN_free(tx);
	BN_free(ty);
	BN_free(m);
	BN_free(k);
	EC_POINT_free(G);
	EC_POINT_free(R);
	EC_POINT_free(T);
	EC_GROUP_free(group);
	BN_CTX_free(ctx);



	//输出结果
    /* here is your code */
    puts(C[0]); // 
    puts(C[1]); //  程序最终要输出这4项,
    puts(S[0]); //  除此以外不可以有别的输出
    puts(S[1]); // 
    return 0;
}