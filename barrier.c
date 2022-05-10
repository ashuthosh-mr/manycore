// Call barrier(no. of threads); in the multi-threaded C program to implement barrier
void barrier(int c)
{
asm volatile ("li t0, 1\n" 
              "li x31,0x0000000081000004\n" //hope nothing is in this address
              "again:\n"
              "amoswap.w.aq t0, t0, (x31)\n" //acquire lock
              "bnez t0, again\n" // if lock not obtained try again
              "lw t1,4(x31)\n"   // add 1 to 4(x31) location
              "addi t1,t1,1\n"
              "sw t1,4(x31)\n"
              "amoswap.w.rl x0, x0, (x31)\n"); //release lock
int check=0;
spin: asm ("lw t2, 4(x31)" :"=r"(check)); //read the contents of 4(x31)
if(check==c) // if it is equal to 4 (4 is the number of threads used) 
return;
else 
goto spin; // spin if the check is not equal to 4

}
