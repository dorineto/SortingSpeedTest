Caso deseja incluir um novo algoritmo de ordenação é preciso que tenha o metódo com a seguinte assinatura:

void sort(int *, int)

Se estiver utilizando o sistema operacional Windows importe o arquivo  windows_sort.h (esse arquivo está disponivel no diretório headers) no seu codigo fonte e utilize a seguinte sequêcia de comandos para compilar o arquivo corretamente:

gcc -c -DBUILD_DLL <nome arquivo fonte>.c
gcc -shared -o <nome arquivo final>.dll <nome arquivo objeto>.o

Se estiver utilizando o sistema operacional Unix/Linux importe o arquivo linux_sort.h (esse arquivo está disponivel no diretório headers) no seu codigo fonte e utilize a seguinte sequência de comandos para compilar o arquivo corretamente:

gcc -shared -fPIC -o <nome arquivo final>.so <nome arquivo fonte>.c

Após feita as intruções acima basta colocar o arquivo .dll ou .so no diretório alg