#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

char OPTION[13] = "bsdciouxX%";


int   size_of(const char *str)
{
  int i;

  i = -1;
  if (str == NULL)
    return (0);
  while (str[++i] != '\0'){}
  return (i);
}

void   print(char *str)
{
  int  i;

  i = -1;
  while (str[++i] != '\0')
      write(1, &str[i], 1);
}

char *errn(char *str)
{
  print(str);
  return (NULL);
}

int err(char *str,int type)
{
  print(str);
  if (type == 0)
    return (-1);
  return (1);
}

int   if_in(char c, char *tab)
{
  int i;

  i = -1;
  while (++i < size_of(tab))
    if (tab[i] == c)
      return (1);
  return (0);
}

char                  *int_str(unsigned long int nbr)
{
  char                *to_ret;
  unsigned long int   i;
  int                 loop;
  int                 tf;

  i = 10000000000;
  loop = 0;
  tf = 0;
  if ((to_ret = malloc(12 * sizeof(char))) == NULL)
    return (errn("Can't allocate memory"));
  while (loop < 12 && i > 0)
  {
    if (((nbr / i) + 48) > 48)
      tf = 1;
    if (tf)
    {
      to_ret[loop++] = ((nbr / i) + 48);
      nbr = nbr - (nbr / i) * i;
    }
    i = i / 10;
  }
  if (loop == 0)
    to_ret[loop++] = '0';
  to_ret[loop] = '\0';
  return (to_ret);
}

char    *char_str(char c)
{
  char  *to_ret;

  if ((to_ret = malloc(2 * sizeof(char))) == NULL)
    return (errn("Can't allocate memory"));
  to_ret[0] = c;
  to_ret[1] = '\0';
  return (to_ret);
}

int   str_copy(char **str, char *old, int char_add)
{
  int i;

  i = -1;
  if ((*str = malloc((size_of(old) + char_add + 1) * sizeof(char))) == NULL)
    return (err("Can't allocate memory",  0));
  while (++i < size_of(old))
    (*str)[i] = old[i];
  (*str)[i] = '\0';
  return (0);
}

int     add(char **str, char *to_add)
{
  char  *str_tmp;
  int   i;
  int   size_add;
  int   size_str;

  i = -1;
  size_add = size_of(to_add);
  size_str = size_of(*str);
  if (str_copy(&str_tmp, *str, 0))
    return (err("Can't copy a string to another", 0));
  free(*str);
  if(str_copy(str, str_tmp, size_add))
    return (err("Can't copy a string to another", 0));
  free(str_tmp);
  while (++i < size_add){
    (*str)[i + size_str] = to_add[i];
  }
  (*str)[i + size_str] = '\0';
  return (0);
}

char *int_bs(int num, int base, int maj)
{
    int i;
    int j;
    char *to_ret;
    char *alpha;

    i = 12;
    j = 0;
    if ((to_ret = malloc(13 * sizeof(char))) == NULL)
      return (NULL);
    if(str_copy(&alpha, (maj) ? "0123456789ABCDEF" : "0123456789abcdef", 0))
      return errn("Can't copy a string to another");
    while(num > 0){
        to_ret[i] = alpha[num % base];
        i--;
        num = num/base;
    }
    free(alpha);
    while ( ++i < 13)
       to_ret[j++] = to_ret[i];
    to_ret[j] = 0;
    return (to_ret);
}

char *ap_to_str(char c, va_list ap)
{
  switch (c)
  {
    case 'c':
      return (char_str(va_arg (ap, int)));
    case 's':
      return ((char *)va_arg(ap, char *));
    case 'i':
    case 'd':
      return (int_str(va_arg (ap, int)));
    case 'o':
      return (int_bs(va_arg (ap, int), 8, 0));
    case '%':
      return (char_str('%'));
    case 'u':
      return (int_str(va_arg (ap, unsigned long int)));
    case 'x':
    case 'X':
      return (int_bs(va_arg (ap, int), 16, (c == 'x') ? 0 : 1));
    case  'b':
      return (int_bs(va_arg (ap, int), 2, 0));
  }
  return (errn("Can't get option"));
}

int     adding(char **string, va_list ap, int i, char d)
{
  char  *c;

  if ((c = (i) ? ap_to_str(d, ap) : char_str(d)) == NULL)
    return (err("Can't get string", 0));
  if (add(string, c) != 0)
    return (err("Can't add string to another", 0));
  if ((i && d != 's') || !i)
      free(c);
  return (0);
}

int       my_printf(const char *str, ...)
{
  va_list ap;
  int     i;
  char    *string;
  int     size;

  size = -1;
  if ((string = malloc(2 * sizeof(char))) == NULL)
    return (1);
  string[0] = '\0';
  va_start(ap, str);
  i = -1;
  while (++i < size_of(str))
    if (str[i] == '%' && i + 1 <= size_of(str) && if_in(str[i + 1], OPTION))
    {
      if (adding(&string, ap, 1, str[++i]) != 0)
        return (err("Can't add option", 0));
    }
    else
      if (adding(&string, ap, 0, str[i]) != 0)
        return (err("Can't add character", 0));
  print(string);
  va_end(ap);
  size = size_of(string);
  free(string);
  return(size);
}

int main()
{
  my_printf(" 1 - une chaine\n");
  my_printf(" 2 - %s\n", "une autre chaine");
	my_printf(" 3 - %i\n", 42);
	my_printf(" 4 - %s %d %s%c", "avec", 4, "parametres", '\n');
  my_printf(" 5 - %o\n", 42);
  my_printf(" 6 - %u\n", (unsigned int)4200000000);
  my_printf(" 7 - %x\n", 42);
  my_printf(" 8 - %X\n", 42);
  my_printf(" 9 - %d%%\n", 42);
  my_printf("10 - binaire de %i: %b\n", 42, 42);
  return (0);
}
