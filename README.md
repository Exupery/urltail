URL Tail
=============

Equivalent of running [tail -f](https://en.wikipedia.org/wiki/Tail_(Unix)) but for a URL (presumably containing a file with periodically updating text) instead of a local file.

Usage
-----

`./urltail <URL>`

Compiling
---------

`g++ urltail.cpp -lcurl -o urltail`

Requirements
------------

* [libcurl](http://curl.haxx.se/libcurl/) - to install [libcurl4-gnutls-dev](http://packages.ubuntu.com/trusty/libcurl4-gnutls-dev) on Ubuntu run `sudo apt-get install libcurl4-gnutls-dev`