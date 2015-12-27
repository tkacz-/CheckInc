# CheckInc
CheckInc checks increments at the binary files and write into the log-file information about the increment:
* '=' means the increment is correct;
* information about the increment errors.
##Settings:
* 2-bytes and 4-bytes numbers;
* Little/Big endian.
##Information about the increment errors
[     #][       DEC =     HEX]	[       DUMP]    [  DISTANSE]    [ LEN]
which has these:
* [ #] - the number of the error;
* [   DEC =   HEX] -  dec is the number of the first increment error, hex is the address of the first increment error;
* [   DUMP] - contains two/four-bytes numbers from the file, which the increment is not true;
* [  DISTANSE] - the number of incorrect bytes;
* [ LEN] - number of the incorrect numbers for this error.
## Copyright 
© Andrei Tkachenko (@tkacz-) include.free@gmail.com
