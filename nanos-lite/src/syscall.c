#include <common.h>
#include "syscall.h"

int sys_write(int fd,void *buf,size_t count){
  if(fd == 1 || fd == 2){
    for(int i = 0; i < count; i++){
      putch(*((char *)buf + i));
    }
    return count;
  }
  return -1;
}

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  //intptr_t ret;
  switch (a[0]) {
    case 0: printf("SYS_exit\n");c->GPRx=0;halt(c->GPRx);break;//SYS_exit
    case 1: printf("SYS_yield\n");yield();break;//SYS_yield
    case SYS_write: c->GPRx = sys_write(c->GPR2,(void *)c->GPR3,(size_t)c->GPR4);break;  
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
  //c->GPRx = ret;
}


