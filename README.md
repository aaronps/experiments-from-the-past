# Linux Video Capture

This was a experiment on capturing video in Linux made around year 2011. It might not work any more, didn't check it. The project used Code::Blocks.

For this experiment I used libsdl for the display window and v4l2 to capture the video. It is not really c++ code if you know what I mean.

What I learned in this experiment was very usefull during the years AND the knowledge was fully usefull on 2015 when I had to do new r&d for a video detection system.

Doing this I learned:

* v4l2: I always wanted to capture some video from the cameras, after several tests, I ended using the memory mapped capture... if remember correctly.

* About the integrated cameras querying and format descriptions

* About FOURCCs and YUV

* Some basic algorithms for video handling and motion monitoring (erosion,threshold,etc)

_(screenshoots included for fun)_