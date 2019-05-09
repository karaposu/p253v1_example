
#include <math.h>
#include <p253.h>


#define NOF_8BIT 5
#define NOF_16BIT 3
#define NOF_FRAC 2
#define NOF_FRAC16 1

 p253_t p253 ;

          
 /*************degişkenler*****************************/
 uint8_t  n0f8 ;uint8_t n0f16;uint8_t noff ;     uint8_t total ; uint8_t noff16 ;uint8_t sbai ;  uint8_t fbai; uint8_t fbai16;

         
             uint8_t frac_act_indx[NOF_8BIT]={1,0,0,0,1};
    
              uint8_t frac_act_indx16[NOF_16BIT]={0,0,1};

    

 
          uint8_t sign_bytes[30]; 
          uint8_t fraction_index_for_8bit_values[30]; 
           uint8_t fraction_index_for_16bit_values[30]; 
          uint8_t fractionpart_8bit[30];   // storage array for 8bit data to be sent over usart ....
          uint8_t decimalpart_8bit[30];   // storage array for 8bit data to be sent over usart ....

             uint8_t fractionpart_16bit[30];   // storage array for 8bit data to be sent over usart ....
          uint16_t decimalpart_16bit[30];   // storage array for 8bit data to be sent over usart ....

          
         int8_t raw_packet_8bit[30];   // storage array for 8bit data to be sent over usart ....
            uint8_t debug_array[30]; 
    
           float data_raw8bit[30]={0};   
            float data_raw16bit[30]={0};   
int8_t  dbg=0;
int16_t  dbg1=0;
int16_t  dbg2=0;



void setup() {

         Serial.begin(9600);


     
  
        /*some test data is appointed to the data arrays */
        data_raw8bit[0]=-1.10;  data_raw8bit[1]=-2.2097;   data_raw8bit[2]=-3.30;  data_raw8bit[3]=-40.407;   data_raw8bit[4]=-5.50;  data_raw8bit[5]=-6.6097;   data_raw8bit[6]=-7.70;  data_raw8bit[7]=-8.807; ;  data_raw8bit[8]=-9.907; 
        data_raw16bit[0]=-1000.100;  data_raw16bit[1]=-2000.200;   data_raw16bit[2]=-3000.30;  data_raw16bit[3]=-4000.407;   data_raw16bit[4]=-5000.50;  data_raw16bit[5]=-6000.60;   data_raw16bit[6]=-7000.70;  data_raw16bit[7]=-8000.807; ;  data_raw16bit[8]=-9000.907; 
        
    



 
p253_init3(&p253,  NOF_8BIT,  NOF_16BIT,  NOF_FRAC, NOF_FRAC16,frac_act_indx,frac_act_indx16);  
                                                                             

      
p253_make_prepackage_signs_8_16( &p253,data_raw8bit ,data_raw16bit,sign_bytes );
        
     
      
p253_make_prepackage_distill_8_16(&p253,  data_raw8bit,fractionpart_8bit, decimalpart_8bit ,data_raw16bit ,fractionpart_16bit ,decimalpart_16bit) ;

  
p253_make_prepackage_create_fraction_index_byte8( &p253,frac_act_indx ,fraction_index_for_8bit_values);
p253_make_prepackage_create_fraction_index_byte16( &p253,frac_act_indx16 ,fraction_index_for_16bit_values);

 
p253_package( &p253,  decimalpart_8bit ,decimalpart_16bit,  fractionpart_8bit  ,fractionpart_16bit,  sign_bytes   , fraction_index_for_8bit_values, fraction_index_for_16bit_values,  debug_array);

  


}

void loop() { }


















