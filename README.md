# CheckInc
CheckInc checks increments at the binary files and write into the log-file information about the increment:

* '=' means the increment is correct;
* information about the increment errors.

## Settings:
* 2-bytes and 4-bytes numbers;
* Little/Big endian.

## Information about the increment errors

[ \___#][ \_____DEC = \_____HEX]	[ \__________DUMP]    [ \__DISTANSE]    [ \_LEN]

which has these:

* [ \___#]- the number of the error;
* [ \_____DEC = \_____HEX] -  dec is the number of the first increment error, hex is the address of the first increment error;
* [ \__________DUMP] - contains two/four-bytes numbers from the file, which the increment is not true;
* [ \__DISTANSE] - the number of incorrect bytes;
* [ \_LEN] - number of the incorrect numbers for this error.
