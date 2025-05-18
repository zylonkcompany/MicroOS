// log functions

extern void klog(const char* message);
extern void log_sys(); 

// This is the start point of kernel
void micro_kernel(){
  log_sys();
  klog("Hello World! I am MicroOS kernel!\n"); // Welcome msg
}

// main
void kmain(){
  micro_kernel(); // call the start point
  for(;;){ // loop for system
    __asm__ volatile ("cli; hlt"); // clear the interrupts and halt the system
  }
}