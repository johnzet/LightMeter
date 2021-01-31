#include <cross_studio_io.h>
#include <usart/usart.h>

void __putchar(int ch)
{
  // debug_putchar(ch);
  USART_Write(AT91C_BASE_US0, ch, 0);

}

int __getchar()
{
  return debug_getchar();
}

long time(unsigned long *p)
{
  return debug_time(p);
}