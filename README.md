# mmix
mmix in C   
<pre>
To generate a simple test program:         
# echo "48 01 00 01 48 02 00 02 20 03 01 02" > test_program.hex  
# xxd -r -p test_program.hex test_program  

To run:  
# make && ./mmix test_program  
</pre>

![mmix](mmix.png)  


