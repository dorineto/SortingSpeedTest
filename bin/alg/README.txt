Caso deseja incluir um novo algoritmo de ordena��o � preciso que tenha o met�do com a seguinte assinatura:

void sort(int *, int)

Se estiver utilizando o sistema operacional Windows importe o arquivo  windows_sort.h (esse arquivo est� disponivel no diret�rio headers) no seu codigo fonte e utilize a seguinte sequ�cia de comandos para compilar o arquivo corretamente:

gcc -c -DBUILD_DLL <nome arquivo fonte>.c
gcc -shared -o <nome arquivo final>.dll <nome arquivo objeto>.o

Se estiver utilizando o sistema operacional Unix/Linux importe o arquivo linux_sort.h (esse arquivo est� disponivel no diret�rio headers) no seu codigo fonte e utilize a seguinte sequ�ncia de comandos para compilar o arquivo corretamente:

gcc -shared -fPIC -o <nome arquivo final>.so <nome arquivo fonte>.c

Ap�s feita as intru��es acima basta colocar o arquivo .dll ou .so no diret�rio alg