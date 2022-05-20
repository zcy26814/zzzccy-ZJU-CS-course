#include <stdio.h>
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
    /* here is your code */
    puts(C[0]); // \\  
    puts(C[1]); //  \\ 程序最终要输出这4项,
    puts(S[0]); //  // 除此以外不可以有别的输出
    puts(S[1]); // //
    return 0;
}
