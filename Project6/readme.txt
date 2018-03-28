Ryan Miyahara
UCID: 804585999

To begin, I ran the original code as it came. Since it does not have
multithreading support, anything after 1-test.ppm could not be created. Below
are the results of the "make clean check" command:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m47.180s
user    0m47.166s
sys     0m0.008s

After doing this, I began adding multithreading support.

My first issue came with the sequence at which the pixels were processed. The
issue this would cause would be seen in the difference check. To fix this, I
created a shared 3D array from the original 1D array titled "shared_color."
The 2 new dimensions would indicate the pixel to which the colors corresponded
to. Next, I implemented a function that went through shared_color and printed
everything in the correct order after all the threads had been completed.

My next issue was a segmentation error. I spent a very long time looking
for the source of this issue. At first, I thought it was casting the arguments
of pthread_create. After checking numerous examples I realized this was not
the case. Next, I used GDB to find the line at which the error occurred. This
showed me it was in my function labelled "process_pixels" which essentially
was the original loop with a few changes to permit multithreading. After
combing over this function I realized there were 2 issues. The first was that
my starting points for each thread were off due to a fencepost error. Secondly,
and the issue which took the longest to find, was that my main loop's
incrementing variable was never incremented. Once I fixed both of these errors,
I ran "make clean check" once again with success. Below are the results:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m46.231s
user    0m46.220s
sys     0m0.006s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m23.419s
user    0m46.725s
sys     0m0.001s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m15.506s
user    0m46.961s
sys     0m0.002s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m9.880s
user    0m47.468s
sys     0m0.002s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done

As we can see, the real time approximately drops by a factor of 2 as the number
of threads is doubled. The user time stays about the same as well due to the
same amount of work still having to be done. Lastly, the sys time stays
relatively the same due to the same amount of system calls being made every
time. Overall, when running the program, multithreading decreased the amount
of time srt took to run from the user's viewpoint by a very noticeable amount.
