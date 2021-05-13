# eratosthenes-steg-decode

### TODO:COMMENTS

### TODO: NICE README


Decoding the message inside the PPM picture using the sieve of Eratosthenes(implemented with bitmap).


You can use my library for bitmaps(creating, destroying, getting bits, setting bits in two variants(inline or macro))


Also here you can find library for ppm images. It processing your input image and decodes message, which is encoded inside it's color bytes. 


It takes ***LSB***s of color bytes, brings it to the new **char**(_8 bits_). When all 8 bits of your new char were set, it pushes your new char into string, which we gonna pring at the end. 


***IF NEW CHAR IS _0000 0000_ program will terminate your string and print it out***


So, you can play with it and decode/encode whatever message with method of encryption.

>Also there is completely stupid error lib, it was necessary for project, bruh
>


***MAKEFILE creates two variants of "primes" program : using inline(-i)/macro functions ***

>"make run" to run both primes progs
>
>./steg-decode _yourImage.ppm_




###### MADE AS SCHOOL PROJECT
