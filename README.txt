
1) Introduction 

This program is a simple touchscreen-enabled calculator. 
It also recognizes dates and times and allows the user to perform 
operations on dates and times.

Examples:

Dates 

3/15/1971 - 0 = 44.663 (currently 44 years old, zero is magic for "now")
3/15/1971 - 9/8/2016 = 45.5178 (will be 45 years old on 9/8/16)
3/15/1971 - 5/2/1983 = 12.1397 (was 12 years old on 5/2/83)

Times

1:15:23 + 3:45 = 01:19:08
1:19:08 ÷ 9.32057 = 00:08:29 (15K runners pace per mile)

The screen is divided into three areas, lower right area is the keypad 
which functions on touchscreen, the upper right area is the input 
display, and the left area is the report.

The report has three columns, "OP", "DATA" and "RES". The "OP" column
shows the operation (ie, +, -, * or ÷), "DATA" shows the input information,'
and "RES" shows the result of the operation. The operation is always 
performed on the current "DATA" and preceeding "RES" value, therefor 
will have a running tally. If you wish to start fresh, press the NEW 
button on the keypad.

2) Keypad Buttons

+		addition operator
-		subtraction operator
*		multiplication operator
÷		division operator
/		date separator
L		future use - unused
Z		future use - unused
0-9		numeric input
:		time separator
.		decimal point
REV		undo/reverse on report
BACK	backspace on input entry
DEL		deletes input entry
NEW		start new calculation in report


3) Key Commands

Delete		deletes input entry
Backspace		backspace on input entry
Q		quit program
X		undo/reverse on report
N		start new calculation in report
L		future use - unused
A		future use - unused
Z		future use - unused
C		copy current result to clipboard
V		paste clipboard to input entry
+		addition operator
-		subtraction operator
*		multiplication operator
/		division operator
Shift+/		date seperator
:		time separator
0-9		numeric input
.		decimal point



4) Building the program

GNU/Linux

# qmake
# make
# cp nugget /usr/bin

FreeBSD

# /usr/local/lib/qt5/bin/qmake
# make
# cp nugget /usr/local/bin


5) Running the program

# nugget

The program will launch full screen by default. 
To launch the program in "normal screen view", ie not fullscreen, use 
the command line parameter "S"

# nugget S


6) Caveats

1.	REV/DEL/BACK can be confusing.

2.	"/" on keyboard is "÷", hold shift plus "/" for date seperator.

3.	If you click on the report area, keyboard entry may not function as
	intended. Click on the keypad to resume keyboard entry.
	
4.	Dates are in USA format, m/d/Y. May use system locale in the future.

5.	Operations performed on times do not use tenths, ie 1:13:01.7

6.	Presently use numeric 10-key or touchscreen. To be fixed in future.

7.	Times may be added or subtracted. Times may be divided by a number. 
	Other time operations may not function as desired.
	
8.	Result table copy is not currently implemented (future release).


7) License

Disposera GUI
	nugget - simple touchscreen-enabled calculator. 
 
Copyright 2015 Waitman Gobble <ns@waitman.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
