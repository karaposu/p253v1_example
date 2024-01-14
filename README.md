# p253

## This project was originally developed in 2018 and I did not maintain it since. I am interested in conducting a benchmark comparison of this protocol against other standard communication protocols. However, my focus has shifted to numerous other new and intriguing areas of interest. 


I've developed a novel serial communication protocol that enables the transmission of an unlimited number of integers and floats over a serial channel. This protocol, distinguished by its simplicity and efficiency, requires only a single line of code for initial calibration between the two communicating ends. After this setup, no additional delimiter-based decoding is necessary.

The primary benefit of this protocol, which I've named P253, is its use of Consistent Overhead Byte Stuffing (COBS). This technique allows for the optimal use of each byte's capacity. For instance, the integer 255 can be transmitted using just one byte, represented as "1111 1111". This is a significant improvement over ASCII-based protocols, which would require three bytes to send the same number, represented as ["0000 0010" (2), "0000 0101" (5), "0000 0101" (5)].

Another key advantage of P253 is its efficient data organization. Once the format is set—deciding the quantity of 8-bit and 16-bit values and how many of the 16-bit values are fractional—there's no need for further coding to manage the segmentation and interpretation of the received data. This streamlines the communication process, making it more straightforward and less error-prone.


**Data Package Composition**: The protocol allows for the transmission of a diverse data package. For example, a package can contain a mix of 8-bit data, 16-bit data, and fractional data, like {255, -125.65, 100, 200, -10500, 62000, -32125.16}.

**Flexibility in Data Addition**: Adding additional 8-bit data to your application is hassle-free. There's no need to modify the delimiter logic in the receiving section.

**Initialization Key**: The only required change is in the initialization key on the receiving side. This key is a sequence of numbers defining the type, order, and meaning of each 8-bit data segment within a package.

**Interpreting the Package**: With the initialization key, the receiver can accurately interpret each value in the package, understanding its corresponding type and order.

**Use of COBS**: The protocol utilizes Consistent Overhead Byte Stuffing (COBS) for sending packages, ensuring efficient and reliable data transmission.

**Fraction Separation**: The first operational step of the protocol is to separate the fractional parts of the data. These fractions are stored in a list, identifying which fraction corresponds to which piece of data.

**Sign Extraction**: The next step involves extracting the sign information from the data and saving it in a separate list. This list also keeps track of which sign is associated with which data segment.

**Package Assembly**: The final step is the assembly of the package. The order of assembly is as follows: sign byte array, 8-bit data array, 16-bit data array, fraction data array, and finally the fraction index. This structured approach ensures that the package is organized for efficient processing and interpretation on the receiving end.

## Initialization Function:
p253_init3: This function is used to initialize the protocol with the following parameters:

	1. Number of 8-bit Values (n_of8bit): This parameter specifies the total number of 8-bit values included in each data package.

	2. Number of 16-bit Values (n_of16bit): This indicates the total number of 16-bit values present in the package.

	3. Fraction-Enabled 8-bit Values (n_of_f): This defines how many of the 8-bit values in the package are permitted to have fractional parts.

	4. Fraction-Enabled 16-bit Values (n_of_f16): Similar to n_of_f, this parameter sets the number of 16-bit values in the package that can include fractional parts.

	5. 8-bit Fraction Index Array (frac_indx_arry for 8-bit): This array outlines the order in which the fraction-enabled 8-bit values appear in the package. For example, if there are three 8-bit values and only the last one has a fractional part, the frac_indx_arry for 8-bit values would be set to 0001.

	6. 16-bit Fraction Index Array (frac_indx_arry for 16-bit): This array functions similarly to the 8-bit fraction index array but is specific to the 16-bit values. It details the order of fraction-enabled 16-bit values within the package.

	7. By setting these parameters, p253_init3 effectively customizes the protocol for the specific data composition of each package, ensuring that the data is transmitted in an organized and interpretable manner.


