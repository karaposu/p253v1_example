# p253v1

# This project is from 2017 and currently unmaintened. I want to benchmark this with current communication protocols. But there are so many new things I am interested in...

I created a serial communication protocol which allows user to send arbitrary number of integers and floats over serial channel in a such way that once two sides are calibrated by a simple code line, there is no further need of delimiter based decoding. Advantage over other protocols is P253 utilizes COBS which uses full capacity of a byte. 

For example to send integer 255, it is enough to send "1111 1111" (only 1 byte), unlike ASCII base protocols which sends 255 in 3 bytes as : 
[ “0000 0010“ (2) , “0000 0101” (5), “0000 0101” (5) ] 

Second advantage of P253 is like mentioned above, once chosen how many values will be send and how many of them are 8 bit values and how many of them will be 16 bit values and how many of these 16 bit values will have fractions there is no need for any further code to split and segment the transmitted data from receiving side.

	//-This protocol allow us to send a package which contains such data  { 255  -125.65 100 200 -10500 62000 -32125.16 }

	//-As you see this package contains different 8bit data, fraction data, 16 bit data all together. 

	//-And if you need to add another 8 bit data in your application you dont have to worry about rearranging the delimeter logic in the receiving part.

	//-All you need to change is initialization key in receiving side

	//-initialization key is a list of numbers which encodes the type and order and meaning of each 8bit data in a package

	//-Once initialization key is known, receiving side will know which value in package correcponds to what. 

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
