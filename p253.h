
// 253***sign_byte_array****8bit_data_array****16bit_data_array***fraction_data_array8bit***fraction_data_array16bit***fraction_index8bit***fraction_index16bit

//-This protocol allow us to send a package which contains such data =  [255  -125.65 100 200 -10500 62000 -32125.16 ]
//-As you see this package contains different 8bit data, fraction data, 16 bit data all together. 
//-And if you need to add another 8 bit data in your application you dont have to worry about rearranging the delimeter logic in the receiving part.
//-All you need to change is initialization key in receiving side
//-initialization key is a list of numbers which encodes the type and order  and meaning of each 8bit data in a package
//-Once initialization key is known receiving side will know which value in package correcponds to what. 
//-Packages send via COBS


//First thing we protocol does is to seperate fraction parts. And we save the fractions in a list as well as which fraction belongs to which data
//Second process is to extract sign information and save them in another list as well as which sign belongs to which data
//Third step is to create a package with order of   *sign_byte_array  *8bit_data_array *16bit_data_array *fraction_data_array *fraction_index


//  p253_init3  initializes with using these values:
	
    //n_of8bit = number of 8bit values in package
	//n_of16bit = number of 16bit values in package
	//n_of_f = how many 8bit values will allowed to have fraction parts  
	//n_of_f16 = how many 16bit values will allowed to have fraction parts  
	//frac_indx_arry = an array which shows the order of fraction enabled 8bit values in the package 
	//( lets say we have three 8bit values and only the last one have a fraction part.In this case frac_indx_arry= 0001  ) 
	//frac_indx_arry = an array which shows the order of fraction enabled 16bit values in the package 
	



//*p253, uint8_t n_of8bit ,uint8_t n_of16bit,   uint8_t n_of_f,   uint8_t n_of_f16, uint8_t *frac_indx_arry, uint8_t *frac_indx_arry16){
  


//	extract_fraction
//	p253_make_prepackage_distill_8_16
//	p253_make_prepackage_signs_8_16
//	p253_package
//	zip2byte_array2
//	p253_make_prepackage_create_fraction_index_byte8
//	p253_make_prepackage_create_fraction_index_byte16

typedef struct {
    int8_t  total_space;
    int8_t  total_number;
    int8_t  n_of_frac;
	int8_t  n_of_frac16bit;
    int8_t  n_of16bit;
    int8_t  n_of8bit;
    
    int8_t  fraction_byte_array_index;
	int8_t  sign_byte_array_lenght;
	int8_t  fraction_byte_array_lenght;
	int8_t  sign_byte_array_index;
	int8_t  sign_byte_array[ 30];
    int8_t  length_of_fractions;
    int8_t  fraction_activation_for_8bits[ 10];
	
	int8_t  frac_indx_arry[ 30]; 
	int8_t  frac_indx_arry16[ 30]; 
	int8_t  fraction_byte_array_lenght16bit;
	

  
}p253_t;


// 253***sign_byte_array****8bit_data_array****16bit_data_array***fraction_data_array***fraction_index
uint8_t p253_init3(p253_t *p253, uint8_t n_of8bit ,uint8_t n_of16bit,   uint8_t n_of_f,   uint8_t n_of_f16, uint8_t *frac_indx_arry, uint8_t *frac_indx_arry16){
  

   uint8_t a=0;  uint8_t b=0;  uint8_t c=0;  uint8_t d=0;  uint8_t e=0;uint8_t f=0;  uint8_t g=0;
   a= n_of8bit     ;      b= n_of16bit     ;   c= n_of_f    ;     d=   ((b+a-1)/8) +1 ;  e=   ((c-1)/8) +1 ;        f= n_of_f16;        g=   ((f-1)/8) +1 ;    

if(c==0){e=0;}  
if(f==0){g=0;}  

p253->n_of_frac16bit=   f ;
p253->n_of_frac=   c ;
p253->n_of16bit=   b;
p253->n_of8bit=    a;

p253->total_number= a+b ;
p253->sign_byte_array_lenght=d; 
p253->fraction_byte_array_lenght= e;
p253->fraction_byte_array_lenght16bit= g;
p253->total_space=  a+2*b+c+d+e+f+g;

    for(int i=0;i<a;i++){p253->frac_indx_arry[ i]= *(frac_indx_arry +i)  ; 
    }
    for(int i=0;i<b;i++){p253->frac_indx_arry16[ i]= *(frac_indx_arry16+i)  ; 
    }

                                                        
                                                         
}

int extract_fraction( float data_f ,uint8_t precision){  
 

    int decimalPart =(data_f* (int) pow(10,precision)  ) -floor (data_f )*(int) pow(10,precision)    ;
    return  decimalPart;
}

int8_t p253_make_prepackage_distill_8_16(p253_t *p253,  float *values_8bit ,uint8_t *a ,uint8_t *b, float *values_16bit ,uint8_t *c ,uint16_t *d){  


    uint8_t n0f16 = p253->n_of16bit; uint8_t  n0f8  =p253->n_of8bit ;uint8_t  frac_indx_arry[n0f8]  ; uint8_t  frac_indx_arry16[n0f16]  ;
    float temp;  int8_t  sign=1;  int8_t  memory=0;

    for(int i=0;i<n0f8;i++){ frac_indx_arry[i]=     p253->frac_indx_arry[ i];}//Serial.print( "frac_indx_arry_inside_distill :");  Serial.print( "  ");   for(int i=0;i< n0f8 ;i++){Serial.print(  frac_indx_arry[i] );  Serial.print( " ");delay(10);}  ;Serial.println();Serial.println();
    for(int i=0;i<n0f16;i++){frac_indx_arry16[i]=     p253->frac_indx_arry16[ i];}//Serial.print( "frac_indx_arry16_inside_distill :");  Serial.print( "  ");   for(int i=0;i< n0f16 ;i++){Serial.print(  frac_indx_arry16[i] );  Serial.print( " ");delay(10);}  ;Serial.println();Serial.println();
    for(int i=0;i<n0f8;i++){
       sign=1; 
       temp  =    *(values_8bit+i);
       if(frac_indx_arry[i]==1){ *(a + memory)  =    extract_fraction(temp ,2);memory++; }
       *(b + i)  =        floor (temp) * sign;

    }
    temp=0;memory=0;
            



   
    for(int i=0;i<n0f16;i++){
       sign=1; 
       temp  =    *(values_16bit+i);
    
       if(frac_indx_arry16[i]==1){
        *(c + memory)  =    extract_fraction(temp ,2);memory++;
       }
       *(d + i)  =        floor (temp) * sign;

    }

                                                            
}



uint8_t p253_init(p253_t *p253, uint8_t n_of8bit ,uint8_t n_of16bit,   uint8_t n_of_f,   uint8_t n_of_f16){
	// 253***sign_byte_array****8bit_data_array****16bit_data_array***fraction_data_array***fraction_index
	
   uint8_t a=0;  uint8_t b=0;  uint8_t c=0;  uint8_t d=0;  uint8_t e=0;uint8_t f=0;  uint8_t g=0;
    a= n_of8bit     ;      b= n_of16bit     ;   c= n_of_f    ;     d=   ((b+a-1)/8) +1 ;  e=   ((c-1)/8) +1 ;        f= n_of_f16;        g=   ((f-1)/8) +1 ;    

if(c==0){e=0;}	
if(f==0){g=0;}	

p253->n_of_frac16bit=   f ;
p253->n_of_frac=   c ;
p253->n_of16bit=   b;
p253->n_of8bit=    a;

p253->total_number= a+b ;
p253->sign_byte_array_lenght=d; 
p253->fraction_byte_array_lenght= e;
p253->fraction_byte_array_lenght16bit= g;
p253->total_space=  a+2*b+c+d+e+f+g;



                                                            
                                                         
}











uint8_t p253_make_prepackage_signs_8_16( p253_t *p253,float *values_8bit ,float *values_16bit,uint8_t *return_array ){   //  (-251 -1602)  (-2 -160)      //    paket :  -251 -2  -1602 -160
  
       uint8_t   signbyte=0;uint8_t  storage=0;uint8_t  index_memory=0;

        uint8_t  n0f8  =p253->n_of8bit ;uint8_t n0f16 = p253->n_of16bit;uint8_t sign_byte_array_index  =  p253->sign_byte_array_index; uint8_t sign_byte_array[10]={0};

     

        for(int i=0;i< n0f8   ;i++){  
                                                                                   
          if( (*(values_8bit+i))<0)   {  signbyte=1 ;  *(values_8bit+i)= *(values_8bit+i)  *-1 ; }else{  signbyte=0; }
               storage=  ( signbyte<<( i-8*sign_byte_array_index) )|storage;   //  0000 0011
          if( i== (8*(sign_byte_array_index+1))-1  )   {      sign_byte_array[sign_byte_array_index]=  storage  ; 
                 storage=0;   sign_byte_array_index++;} else {sign_byte_array[sign_byte_array_index] = storage  ; }
             index_memory=i;  //i =8      00000001     11011100 
        }
       signbyte=0 ;

         for(int i=0;i< n0f16   ;i++){   if( (*(values_16bit+i))<0)   {  signbyte=1 ;  *(values_16bit+i)= *(values_16bit+i)  *-1 ;  }else{  signbyte=0;}
         storage=  ( signbyte<<( i+index_memory-8*sign_byte_array_index+1) )|storage;   //  0000 0011
         if( i+index_memory+1== (8*(sign_byte_array_index+1))-1 )   {   sign_byte_array[ sign_byte_array_index]  = storage  ; storage=0;     sign_byte_array_index++;}
		 else{sign_byte_array[ sign_byte_array_index]  = storage  ; }

        }

        for(int i=0;i<sign_byte_array_index+1;i++)
        {
          
                *(return_array + i) = sign_byte_array[i];
        }
 

        
}




uint8_t p253_package( p253_t *p253,uint8_t *values_8bit ,uint16_t *values_16bit,uint8_t *values_fraction,uint8_t *values16bit_fraction,uint8_t *sign_array,uint8_t *frac_indexarray,uint8_t *frac_indexarray16,uint8_t *return_array){



// 253***sign_byte_array****8bit_data_array****16bit_data_array***fraction_data_array8bit***fraction_data_array16bit***fraction_index8bit***fraction_index16bit

  uint8_t  n0f8  =p253->n_of8bit ;         uint8_t n0f16 = p253->n_of16bit;                     uint8_t noff = p253->n_of_frac;     uint8_t total = p253->total_space; 
  uint8_t noff16 = p253->n_of_frac16bit;
  uint8_t sbai = p253->sign_byte_array_lenght;  uint8_t fbai = p253->fraction_byte_array_lenght; uint8_t fbai16 = p253->fraction_byte_array_lenght16bit;




        uint8_t   raw_packet_8bit[total] ;


         for(int i=0;i<sbai ;i++){ raw_packet_8bit[i]=*(sign_array+i);}
         for(int i=0;i<n0f8;i++){   raw_packet_8bit[i+sbai]=*(values_8bit+i);}
         
         for(int i=0  ;i< n0f16;    i++){  
          raw_packet_8bit[(i*2+sbai+n0f8)+0]= (  *(values_16bit+i) & 0x00FF    ); // 0 i�in 12 ye  yazd�r�r.   1 i�in 14 e yazd�r�r 
          raw_packet_8bit[(i*2+sbai+n0f8)+1]=  ( *(values_16bit+i) )>> 8 ;        //  0  i�in 13 e yazd�r�r.    1 i�in 15 e yazd�r�r.
         }
         for(int i=0  ;i< noff;    i++){ raw_packet_8bit[sbai+n0f8+n0f16*2+i]=*(values_fraction+i); }
          for(int i=0  ;i< noff16;    i++){ raw_packet_8bit[sbai+n0f8+n0f16*2+noff+i]=*(values16bit_fraction+i); }

          
         for(int i=0  ;i< fbai;    i++){raw_packet_8bit[sbai+n0f8+n0f16*2+noff+noff16+i]=*(frac_indexarray+i); }
          for(int i=0  ;i< fbai16;    i++){raw_packet_8bit[sbai+n0f8+n0f16*2+noff+noff16+fbai+i]=*(frac_indexarray16+i); }
         for(int i=0;i<  total   ;i++)
        {
          
                *(return_array + i) = raw_packet_8bit[i];
        }
       

}





/*


uint8_t p253_make_prepackage_signs_8_16( p253_t *p253,float *values_8bit ,float *values_16bit,uint8_t *return_array ){   //  (-251 -1602)  (-2 -160)      //    paket :  -251 -2  -1602 -160
  
uint8_t   signbyte=0;uint8_t  storage=0;uint8_t  index_memory=0;

 uint8_t  n0f8  =p253->n_of8bit ;
 uint8_t n0f16 = p253->n_of16bit;
 uint8_t sign_byte_array_index  =  p253->sign_byte_array_index;

 int16_t  negative_number=-240;

uint8_t sign_byte_array[10]={0};

   
        for(int i=0;i< n0f8   ;i++){  
                                                                                   
          if( (*(values_8bit+i))<0)   {  signbyte=1 ;  
        
            *(values_8bit+i)= *(values_8bit+i)  *-1 ; }
         else{ 
            signbyte=0;
            }
                                //      Serial.print("i :"); Serial.print(i); Serial.print(" , ");      Serial.print("dbg1 :"); Serial.print(*(values_8bit+i)); Serial.print(" , "); Serial.print("sign_byte :"); Serial.print(signbyte);  Serial.print(" , "); Serial.print("sb_index :"); Serial.print(sign_byte_array_index);   Serial.println( );              
           storage=  ( signbyte<<( i-8*sign_byte_array_index) )|storage;   //  0000 0011
                                  //      Serial.print("storage :"); Serial.print(storage);  Serial.println( ); 

            
            if( i== (8*(sign_byte_array_index+1))-1  )   {      
                                                   //  p253. sign_byte_array[ sign_byte_array_index]  = storage  ; 
                      sign_byte_array[sign_byte_array_index]=  storage  ; 
                                                            //  sign_byte_array[0]=     p253.sign_byte_array[0];
                  //    Serial.print("sign_array : ");    Serial.println(   sign_byte_array[0] );        Serial.println( );                                                            
                          storage=0;   sign_byte_array_index++;
                 //   Serial.print("sign_byte_array_index : ");    Serial.println(   sign_byte_array_index );        Serial.println( );  
            }
            else
            {
                     sign_byte_array[sign_byte_array_index] = storage  ; 
                                    
              }
             index_memory=i;  //i =8      00000001     11011100 
        }
       signbyte=0 ;

    
      //  for(int i=0;i<sign_byte_array_index+1;i++)
      //  { *(return_array + i) = sign_byte_array[i];}
   
  
   // Serial.println( ); Serial.print("16bitlik alan icin index memory  :"); Serial.print(index_memory);   Serial.print("storage :"); Serial.print(storage); Serial.println( );
   
           for(int i=0;i< n0f16   ;i++){  
                         
       
           if( (*(values_16bit+i))<0)   {  signbyte=1 ;  
            *(values_16bit+i)= *(values_16bit+i)  *-1 ;           }
            
         else{ 
            signbyte=0;
            }

//1     11011100 
//01     11011100 i=0
//001     11011100   i=1
//1001     11011100   i=2
//11001     11011100   i=3
//111001     11011100   i=4
//0111001     11011100   i=5
//01011 1001     11011100   i=6
//      11  01011 1001     11011100   i=7

 
    //   Serial.print("i :"); Serial.print(i); Serial.print(" , ");      Serial.print("dbg2 :"); Serial.print(*(values_16bit+i)); Serial.print(" , "); Serial.print("sign_byte :"); Serial.print(signbyte);  Serial.print(" , "); Serial.print("sb_index :"); Serial.print(sign_byte_array_index);   Serial.println( );              
  
          //storage=  ( signbyte<<( i-8*sign_byte_array_index) )|storage;   //  0000 0011               
           storage=  ( signbyte<<( i+index_memory-8*sign_byte_array_index+1) )|storage;   //  0000 0011
    //   Serial.print("storage :"); Serial.print(storage); Serial.println(); 

            if( i+index_memory+1== (8*(sign_byte_array_index+1))-1 )   {   //   if( i== (8*(sign_byte_array_index+1))-1  ) 
                sign_byte_array[ sign_byte_array_index]  = storage  ; 
                storage=0;     sign_byte_array_index++;
            }else
            {
                sign_byte_array[ sign_byte_array_index]  = storage  ; 
              }

        }

        for(int i=0;i<sign_byte_array_index+1;i++)
        {
            // Serial.print("sign_byte_array ");   Serial.print(i);Serial.print(": "); Serial.println( sign_byte_array[i] ); 
                *(return_array + i) = sign_byte_array[i];
        }
 

        
}

*/














int8_t zip2byte_array2( uint8_t *values ,uint8_t number_of_boolean,int8_t *return_array){

     uint8_t byte_array_index =0;uint8_t   fid=0; uint8_t  storage=0;uint8_t  index_memory=0;
     uint8_t temp_array[30]={0};

     
  for(int i=0;i< number_of_boolean   ;i++){  
                                                            
            fid=*(values+i);
            storage=  ( fid<<( i-8*byte_array_index) )|storage;   //  0000 0
                                                                                 
            if( i== (8*(byte_array_index+1))-1  )   {  
                                                                                                              
                temp_array[byte_array_index]=  storage  ; 
                 storage=0; byte_array_index++;
            }
      else
            {
            temp_array[byte_array_index] = storage  ;
            }
         index_memory=i;
        }
        for(int i=0;i<byte_array_index+1;i++)
        {       *(return_array + i) = temp_array[i];
           }
    
}

  void p253_make_prepackage_create_fraction_index_byte8(p253_t *p253, int8_t *values ,int8_t *return_array ){  
                                                                      
      int8_t return_array_inception[15];uint8_t  zero=0; uint8_t n = p253->n_of8bit;
      if(n != zero){
        zip2byte_array2( values,  n ,return_array_inception); 
        for(int i=0;i<   ((n-1)/8) +1         ;i++){ *(return_array + i) = return_array_inception[i];}
            
                  }
    }

uint8_t p253_make_prepackage_create_fraction_index_byte16(p253_t *p253, int8_t *values ,int8_t *return_array ){  
                                                                      
      uint8_t nof16 = p253->n_of16bit; int8_t return_array_inception[30]; uint8_t  zero=0;   
      if(nof16 != zero){
      zip2byte_array2( values,nof16 ,return_array_inception);  
       for(int i=0;i<   ((nof16-1)/8) +1         ;i++){ *(return_array + i) = return_array_inception[i];}
      }
    }


  
	
	




