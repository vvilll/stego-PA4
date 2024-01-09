# PA4: Digital Steganography

## Learner Objectives
At the conclusion of this lab assignment, participants should be able to:
* Use command line arguments
* Use C++ bitwise operators
* Understand the composition of images
* Understand the basics of digital steganography
* Encode and decode hidden messages in images


## Digital Steganography
"Steganography is the practice of concealing a file, message, image, or video within another file, message, image, or video [Wikipedia](https://en.wikipedia.org/wiki/Steganography)". You can try stenography online through this [link](http://stylesuxx.github.io/steganography/).

![Steganography Example](https://miro.medium.com/max/519/0*rLECUN69yVKuX0nQ.png)
> Image Source: [The Threat of Digital Steganography-cloaked Malware to U.S. Critical infrastracture Systems](https://z3r0trust.medium.com/the-threat-of-digital-steganography-cloaked-malware-to-u-s-critical-infrastructure-systems-aff428db8ac7)

## Assignment details
In this assignment, you will need to create a command line tool called stegoBMP that encodes massage in BMP files (specifically 24 bits BMP files without compression) using LSB (least significant bit) technique. The tool will accept command line arguments. -d, -e, -f, and -o called flags. The flags can be used in a different order. -d flag stands for decoding, -e flag stands for encoding, -f specifies the name of the input file, -o specifies the name of the output file. -f flag and -o flag must be followed by the file name.
The examples of legal command line arguments are below:
```bash
 ./stegoBMP -e -f cover.bmp -o secret.bmp
 ./stegoBMP -e -o secret.bmp -f cover.bmp
 ./stegoBMP -o secret.bmp -e -f cover.bmp
 ./stegoBMP -o secret.bmp -f cover.bmp -e
 ./stegoBMP -f cover.bmp -e -o secret.bmp
 ./stegoBMP -f cover.bmp -o secret.bmp -e
 ./stegoBMP -d -f secret.bmp
 ./stegoBMP -f secret.bmp -d
```
No other command line arguments should be accepted unless you choose to do Extra Credit.
```bash
 ./stegoBMP -e -d -f cover.bmp -o secret.bmp
The correct format for encoding
         ./stegoBMP -e -f <cover.bmp> -o <secret.bmp>
The corect format for decoding
         ./stegoBMP -d -f <secret.bmp>
```
### Encoding
If the user chooses the encoding option, the program should 
- [ ] Check if a given file is the BMP file without encoding. If it is not, give an error message and terminate the program.
- [ ] Ask the user to enter a message.
- [ ] Check if the message is small enough to fit in the given image. If not, let the user know.
- [ ] Open a new file specified by -o flag
- [ ] Start copying the original image into this file.
- [ ] Save the length of the message (in bytes or bits, your choice) in the metadata (header) of the file. I recommend using the four bytes starting at position 6. 
- [ ] Copy the rest of the headers until the pixel array
- [ ] Brake massage in the bits and incode each bit in LSB. Write new values for the bytes in the output file.
- [ ] After you are done with the message, copy the rest of the BMP file unchanged.

### Decoding

If the user chooses the decoding option, the program should 
- [ ] check if a given file is the BMP file without encoding. If it is not, give an error message and terminate the program.
- [ ] Read the length of the massage in the metadata (header) of the file. If there is nothing there, let the user know that file does not have any encoding.
- [ ] Read the secret message and display it to the user.

### Extra Credit

- [ ] Add an addition option -n that specifies the number of bits used. So far we only changed one last bit, however, we can probably go up 3 or 4  bits without noticeable change. Play with it and see the limit. (10 pts)
- [ ] In this assignment we only used 24-bit pixel format BMP file. Read through other types of non-compressed BMP file formats. Adjust your program if needed to work on all of them. (10 pts)
- [ ] Use classes for this assignment (10 pts)



## Submitting Assignments
* It is VERY IMPORTANT that besides pushing the code to GitHub that you still submit the GitHub URL of this lab assignment in Canvas. This allows the instructor to be notified of your final submission.
