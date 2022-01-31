# p253v1

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
