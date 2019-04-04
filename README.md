# myprintf

*`int       my_printf(const char \*str, ...)`*

Le caractère spécificateur de conversion type précise si l’argument correspondant doit être interprété comme un caractère, une chaîne, un entier ou un nombre à virgule flottante. Le caractère type, qui est le seul champ de spécification de conversion obligatoire, apparaît après tous les champs facultatifs.
  
Caractère  | Argument | Format de sortie 
------------ | ------------- |  ------------
c	| Caractère | Spécifie un caractère codé sur un octet.
d	| Entier	| Entier décimal signé.
i	| Entier	| Entier décimal signé.
o	| Entier	| Entier octal non signé.
u	| Entier	| Entier décimal non signé.
x	| Entier	| Entier hexadécimal non signé ; utilise « abcdef ».
X	| Entier	| Entier hexadécimal non signé ; utilise « ABCDEF ».
s	| Chaîne  | Spécifie une chaîne de caractères codés sur un octet ou multioctets.
o	| Entier	| Entier bianire non signé.
% |  *none* | Spécifie le caractère '%'.
