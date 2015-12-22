# E27radio

![E27radio](https://raw.githubusercontent.com/jevontech/e27radio/master/0.ProjectReport/images/overview.jpg)

This Github repository contains the sourcecode for the E27radio application.
E27radio is an internet radio client based on the Intel Edison platform.

This sourcecode needs to be used together with the Intel Edison BitBake image.
This repository can be found at:
https://github.com/jevontech/e27radio-image 


## How to install E27radio on your Intel Edison

* Build a new Intel Edison image using the bitbake recipe at https://github.com/jevontech/e27radio-image. Check out the Intel Edison website for more information on how to build an image.
* Build the e27radio software in this repository using a cross-compiler toolchain (requires a Linux PC with a recent CMake version, build-tools and the SDK build from e27radio-image sources). 
You might need to adjust the Cmake toolchain file to point to the SDK.
* Copy the e27radio software to the Intel Edison and run it..

I will eventually include the build of e27radio as a bitbake recipe in the e27radio-image ..... this will make it a lot easier to use.
