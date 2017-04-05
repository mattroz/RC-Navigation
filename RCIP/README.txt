	================================================
	|	RCIP - RoboCake Instruction Protocol	|
	================================================


	     RoboCake chassis							
		    
		 FORWARD
		    ^
		    |
	    _________________
     	  /     	      \
        /           		\
      /	                          \
    /       	                    \
  /	  LE   	             RE	      \
  |     +----+		   +----+     |
  |	|    |		   |	|     |
  |     |    |             |    |     |
  |     +----+             +----+     |
   \	  		             /
    \	  		 	    /
      \   			  /
	\ 			/
	  \___________________/

LE - left engine
RE - right engine
	
Values can vary from -37 to +37 in integer.


 ==================
  PACKET STRUCTURE
 ==================
RCIP instruction packet (rcip_instr_pack_t at RCIP/rcip.h):
	--> left engine value
	--> right engine value

==================
 PACKET WRAPPING
==================

 LE value	   \       +---------------------+     +--------------------------------+
 pointer to packet  } ---> | wrap_instr_packet() | --> | wrapped packet for PC104 board |
 RE value 	   /       +---------------------+     +--------------------------------+
