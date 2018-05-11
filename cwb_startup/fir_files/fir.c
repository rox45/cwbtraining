/*****************************************************************
 * PolyU EIE4110 HLS Laboratory
*
* Date: 23/2/2016
 ****************************************************************/


#include <bdlstd.h>

#define TAPS 5


#ifdef C

int  data[TAPS];
int coeff[TAPS];
int sop;

#else
in ter(7..0)  data[TAPS];
in ter(7..0) coeff[TAPS];
out ter(7..0) sop;

#endif

/*------------------------------------------------------  
 * filter 
 *------------------------------------------------------  */
unsigned char filter(
    unsigned char *data,
    unsigned char*coeff  )
{


 int sum;
 unsigned char i ;

    sum = 0 ;

    /*--- multiplication and summation -----------------*/
    for(i=0;i<TAPS;i++){
       sum += data[i] * coeff[i] ;

   } 
    /*--- rounding -------------------------------------*/
    if ( sum < 0 ){
        sum = 0 ;
    } else if ( sum > 255 ){
        sum = 255;
    }

    return sum;
}

/*------------------------------------------------------  
 * Top process function to be synthesized 
 *------------------------------------------------------  */
#ifdef C
void fir() {
#else
process fir(){
#endif

    unsigned char osop ; 
    unsigned char idata[TAPS];
    unsigned char i ;
    unsigned char icoeff[TAPS] ;

    for(i=0;i<TAPS;i++){
       idata[i] = data[i];
       icoeff[i] = coeff[i];
    }
   osop= filter(idata, icoeff);
    sop = osop ;
}


/*------------------------------------------------------  
 * ANSI-C test bench 
 *------------------------------------------------------  */
#ifdef C
int main(){

    FILE *fp_i1, *fp_i2, *fp_o;
    FILE *fp_i1clv, *fp_i2clv, *fp_i3clv, *fp_i4clv, *fp_i5clv;
    FILE *fp_c1clv, *fp_c2clv, *fp_c3clv, *fp_c4clv, *fp_c5clv;
    FILE *fp_oclv;
    int i;
    
    if((fp_i1 = fopen("coeff.txt", "r")) == NULL){
	printf(" \"coeff.txt \" could not be opened.\n");
	exit(1);
    }
    if((fp_i2 = fopen("indata.txt", "r")) == NULL){
	printf(" \"indata.txt \" could not be opened.\n");
	exit(1);
}

    if((fp_i1clv = fopen("data_a00.clv", "w")) == NULL){
	printf(" \"indata_a00.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_i2clv = fopen("data_a01.clv", "w")) == NULL){
	printf(" \"indata_a01.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_i3clv = fopen("data_a02.clv", "w")) == NULL){
	printf(" \"indata_a02.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_i4clv = fopen("data_a03.clv", "w")) == NULL){
	printf(" \"indata_a03.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_i5clv = fopen("data_a04.clv", "w")) == NULL){
	printf(" \"indata_a04.clv \" could not be opened.\n");
	exit(1);
    }

    if((fp_c1clv = fopen("coeff_a00.clv", "w")) == NULL){
	printf(" \"indata_a00.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_c2clv = fopen("coeff_a01.clv", "w")) == NULL){
	printf(" \"indata_a01.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_c3clv = fopen("coeff_a02.clv", "w")) == NULL){
	printf(" \"indata_a02.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_c4clv = fopen("coeff_a03.clv", "w")) == NULL){
	printf(" \"indata_a03.clv \" could not be opened.\n");
	exit(1);
    }
    if((fp_c5clv = fopen("coeff_a04.clv", "w")) == NULL){
	printf(" \"indata_a04.clv \" could not be opened.\n");
	exit(1);
    }

    if((fp_o = fopen("sop.txt", "w")) == NULL){
	printf(" \"sop.txt \" could not be opened.\n");
	exit(1);
    }

    if((fp_oclv = fopen("sop.clv", "w")) == NULL){
	printf(" \"sop.clv\" could not be opened.\n");
	exit(1);
    }



    for (i = 0; i < TAPS; i++){
	if (fscanf(fp_i1, "%d", &coeff[i]) == EOF) exit(0);
    }

    for (;;){
	for (i = 0; i < TAPS; i++){
	    if (fscanf(fp_i2, "%d", &data[i]) == EOF) exit(0);
	}

	fprintf(fp_i1clv, "%d\n", data[0]);
	fprintf(fp_i2clv, "%d\n", data[1]);
	fprintf(fp_i3clv, "%d\n", data[2]);
	fprintf(fp_i4clv, "%d\n", data[3]);
	fprintf(fp_i5clv, "%d\n", data[4]);

	fprintf(fp_c1clv, "%d\n", coeff[0]);
	fprintf(fp_c2clv, "%d\n", coeff[1]);
	fprintf(fp_c3clv, "%d\n", coeff[2]);
	fprintf(fp_c4clv, "%d\n", coeff[3]);
	fprintf(fp_c5clv, "%d\n", coeff[4]);


	fir();

	fprintf(fp_o, "%d\n", sop);
	fprintf(fp_oclv, "%d\n", sop);
    }

  fprintf(fp_i1clv, "\n");
  fprintf(fp_i2clv, "\n");
  fprintf(fp_i3clv, "\n");
  fprintf(fp_i4clv, "\n");
  fprintf(fp_i5clv, "\n");
 
  fprintf(fp_c1clv, "\n");
  fprintf(fp_c2clv, "\n");
  fprintf(fp_c3clv, "\n");
  fprintf(fp_c4clv, "\n");
  fprintf(fp_c5clv, "\n");

  fprintf(fp_oclv, "\n");

    fclose(fp_i1);
    fclose(fp_i2);
    fclose(fp_o);

    fclose(fp_i1clv);
    fclose(fp_i2clv);
    fclose(fp_i3clv);
    fclose(fp_i4clv);
    fclose(fp_i5clv);

    fclose(fp_c1clv);
    fclose(fp_c2clv);
    fclose(fp_c3clv);
    fclose(fp_c4clv);
    fclose(fp_c5clv);

    fclose(fp_oclv);


}

#endif
