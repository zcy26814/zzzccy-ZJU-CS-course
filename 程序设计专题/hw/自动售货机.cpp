#include<stdio.h>
int main(void)
{
  char a[10][20] = {"Table-water","Table-water","Table-water","Coca-Cola","Milk","Beer","Orange-Juice","Sprite","Oolong-Tea","Green-Tea"};
  int b[11] = {0,0,0,0,0,0,0,0,0,0,0};
  int c[50];
  int i=1, k, sum = 0, money, SUM = 0, change, flag=0;
  
  scanf("%d",&money);//�����ֵ�������ܱ�ֵ
  while((money!=-1)&&(money <= 10))
  {
    sum = sum + money;
    scanf("%d",&money);
  }
  
  scanf("%d",&c[i]);
  while(c[i]!=-1)//��ѡ�Ļ����Ŵ洢������c�в���������
  {
    switch(c[i])
    {
      case 1: case 2: case 3: SUM = SUM + 1;break;
      case 4: case 5: SUM = SUM + 2;break;
      case 6: case 7: case 8: SUM = SUM + 3;break;
      case 9: case 10: SUM = SUM + 4;break;
      default:break;
    }
    if(SUM>sum)
    {
      printf("Insufficient money");
      flag = 1;
      break;
    }
    i++;
    scanf("%d",&c[i]);
  }
  change = sum-SUM;
  
  //������bͳ�Ƹ�����Ʒ����
  i = 1;
  while(c[i]!=-1)
  {
    switch(c[i])
    {
      case 1: b[1]++;break;
      case 2: b[2]++;break;
      case 3: b[3]++;break;
      case 4: b[4]++;break;
      case 5: b[5]++;break;
      case 6: b[6]++;break;
      case 7: b[7]++;break;
      case 8: b[8]++;break;
      case 9: b[9]++;break;
      case 10: b[10]++;break;
      default:break;
    }
    i++;
  }
  
  //������
  if(flag==0)
  {
    printf("Total:%dyuan,change:%dyuan\n",sum, change);
    for(i=1; i<=10; i++)
    {
      if(b[i]==0)
        continue;
      else
      {
        printf("%s:%d;",a[i-1],b[i]);
      }
    }
  }
  
  return 0;
}
