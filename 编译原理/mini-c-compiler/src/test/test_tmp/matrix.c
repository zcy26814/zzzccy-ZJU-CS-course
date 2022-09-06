int arrayA[100]; // 10 * 10
int arrayB[100];
int ans[100]; // result

int main()
{
    int MA = 0; // row_A
    int NA = 0; // col_A
    int MB = 0; // row_B
    int NB = 0; // col_B
    int MC = 0; // row_C
    int NC = 0; // col_C
    int i = 0; // row
    int j = 0; // col
    int i_a = 0;
    int i_b = 0;

    // read matrix A
    scan(MA, NA);
    while (i<MA){
        while (j<NA){
            scan(arrayA[i*NA+j]);
            // printf("%d ",arrayA[i*NA+j]);
		    j += 1;
        }
	    // println("");
        j = 0; 
        i += 1;
    }   
    
    scan(MB, NB);
    if (NA!=MB) {
        printf("incompatible dimensions of two arrays");
        return 0;
    }

    // read matrix B
    i = 0;
    j = 0;
    while (i<MB){
        while (j<NB){
            scan(arrayB[i*NB+j]);
            // printf("%d ",arrayA[i*NA+j]);
            j += 1;
        }
	    // println("");
        j = 0; 
        i += 1;
    }
      
    MC = MA;NC = NB;
    i = 0;j = 0;
    int tmp = 0;
	
    while ( tmp < 100 ) {
	    ans[tmp] = 0;
		tmp += 1;
    }

    while (i<MC){
        while (j<NC){
            // arrayA的第i行和arrayB的第j列相乘
            i_a = 0;
            i_b = j;
			// println("i = %d, j = %d, NC = %d",i,j,NC);
            int temp;
			temp = j+i*NC;
			// println("temp = %d",temp);
			while (i_a<NA){
                ans[temp] = ans[temp] + arrayA[i*NA+i_a]*arrayB[i_b];
                // println("ans[%d] = %d",temp,ans[temp]);
				i_a += 1;
                i_b += NB;
            }
            j += 1;
        }
        j = 0;
        i += 1;
    }

    i = 0;
    j = 0;
   	println("calculated answer below:");
    while (i<MC){
        while (j<NC){
            printf("%d ", ans[i*NC+j]);
            j += 1;
        }
        println("");
        j = 0; 
        i += 1;
    }  

    return 0;
}
