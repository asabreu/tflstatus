# tflstatus

An application to retrieve [tube status][tfl] from TFL and display the output in the UNIX console.

Using Serge Zaitsev's [awesome jsmn JSON parsing library][jsmn], supported by [the cURL project's libcurl][libcurl]. 

[tfl]: https://api.tfl.gov.uk/line/mode/tube/status?detail=true
[jsmn]: https://github.com/zserge/jsmn
[libcurl]: http://curl.haxx.se/libcurl/

Features
--------

* portable (tested on x86, ARM)
* small code footprint

Install
-------

To clone the repository you should have Git installed. Just run:

	$ git clone https://github.com/asabreu/tflstatus

To build the application, run `make`.

If build was successful, you should get a `tflstatus` binary.
