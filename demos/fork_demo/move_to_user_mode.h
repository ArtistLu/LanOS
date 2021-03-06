#ifndef MOV_TO_USER_MODE_H
#define MOV_TO_USER_MODE_H
#define move_to_user_mode()      \
  __asm__(                       \
      "movl %%esp,%%eax\n\t"     \
      "pushl $0x17\n\t"          \
      "pushl %%eax\n\t"          \
      "pushfl\n\t"               \
      "pushl $0x0f\n\t"          \
      "pushl $1f\n\t"            \
      "iret\n"                   \
      "1:\tmovl $0x17,%%eax\n\t" \
      "mov %%ax,%%ds\n\t"        \
      "mov %%ax,%%es\n\t"        \
      "mov %%ax,%%fs\n\t"        \
      "mov %%ax,%%gs" ::         \
          : "ax")
#define sti() __asm__("sti" ::)

#define _syscall0(type, name)                                       \
  type name(void) {                                                 \
    long __res;                                                     \
    __asm__ volatile("int $0x80" : "=a"(__res) : "0"(__NR_##name)); \
    if (__res >= 0) return (type)__res;                             \
    return -1;                                                      \
  }
#endif