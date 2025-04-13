#Tinckercad codes for Internet of Things practical labs.

##Lab1
8-key tone generator using Arduino uno board

###Task -1
The tone generator will have 8 push-button switches read by the Arduino uno-board as digital inputs.  Pressing each of the keys should generate a tone through a speaker connected to the Arduino board via a digital output.  The eight keys are assigned with the following tone-frequencies; 300Hz, 400Hz, 500Hz, 600Hz, 700Hz, 800Hz, 900Hz and 1kHz.  Pressing the key momentarily will generate the tone for 20mS while pressing and holding the key will generate the tone continuously without any break.  When more than one key is pressed at the same time, the generated tone will have a frequency equivalent to the sum of the frequencies assigned to each key.

###Task -2
Added a 7-segment display to the circuit and modified the code to display the key number being pressed.  If more than 1 key is pressed, the display will alternate the key numbers at 500mS intervals.
