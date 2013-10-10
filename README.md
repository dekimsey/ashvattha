#Ashvatta

This is a fork of the [Ashvatta](https://github.com/cmaher/ashvattha)
procedural world generation project. This fork is simply a stripped down
[Simplex](http://en.wikipedia.org/wiki/Simplex_noise) noise generator.

Why? Because all the other C++ simplex noise libraries are GPL'd (not LGPL)
which kind of makes them hard to use in a private project.

##Building

    % mkdir build
    % cmake ..
    % make

##Requirements
The basic library itself will be designed to work in any (C++11) environment.

##License
MIT License, see [LICENSE.md]

