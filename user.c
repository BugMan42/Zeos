#include <libc.h>

char buff[24];

int pid;

void test_write() {
	char buffer[3] = "abc";
	write(1,buffer,3);
	write(1,"abc",3);
	write(1,"AAA",3);
}

void test_getpid() {
	char a[10];
	int ticks = getpid();
	itoa(ticks, a);
	write(1,a,1);
}

void test_gettime() {
	char a[10];
	int ticks = gettime();
	itoa(ticks, a);
	write(1,a,3);
}

long inner(long n) 
{
	int i;
	long suma;
	suma = 0;
	for (i=0; i<n; i++) suma = suma + i;
	return suma;	
}
long outer(long n) 
{
	int i;
	long acum;
	acum = 0;
	for (i=0; i<n; i++) acum = acum + inner(i);
	return acum;	
}

int add1(int par1, int par2) {
	return par1+par2;
}

/*
//no input/ouput inline
int add2(int par1, int par2) {
	//  no fa falta ja ho fa
	//  "pushl %ebp;"
	//	 "movl %esp, %ebp;"
	asm("movl 8(%ebp), %eax;"
		 "movl 12(%ebp), %ecx;"
		 "addl %ecx, %eax;");
	// "movl %ebp, %esp;"
	//	 "popl %ebp;"
	//	 "ret;"
}*/
//input/ouput inline
int add_v2(int par1, int par2) {
	int var;
	asm("addl %%ecx, %%eax"
		 : "=r" (var)
		 : "a" (par1), "c" (par2) );
	return var;
}

void print(int number) {
	char str[1];
	itoa(number, str);
	write(1,str,1);
}
void print2(char *aux, int size) {
	write(1,aux,size);
} 
void test_fork() {
	int pid = fork();
	if (pid == 0) {
		//exit();
		while (1) {
			print2("fill",4);
			//exit();
		}
	}
	else if (pid > 0) {
		int i = 0;
		while (1) {
			print2("pare",4);
			++i;
		}
	}
	else {
		print2("error",5);
	}
	//int j = 0;
    while(1) {
    	//write(1,"init",4);
    	//int aux = getpid();
    	//if (j == 100000 || j == 1000000)
    		//test_getpid();
    	/*if ( pid != aux) {
    		print(aux);
    		pid = aux;
    		//test_gettime();
    	}*/
    	//++j;
    		int pid = getpid();
    		print(pid);
    }
}
void nothing() {
	char str[12] = "Inside clone";
	print2(str, strlen(str));
	exit();
}
void thread1() {
	//sem_wait(0);
	char str[12] = "Ping";
	print2(str, strlen(str));
	exit();
}
void thread2() {
	//sem_wait(1);
	char str[12] = "Pong";
	print2(str, strlen(str));
	//while (1) {;}
	exit();
}

void test_clone() {
	char stack1[100];
	char stack2[100];
	sem_init(0,0);
	sem_init(1,0);
	//fork();
	//clone(nothing,stack);
	clone(thread1, &stack1[99]);
	clone(thread2, &stack2[99]);
	sem_signal(0);
	sem_signal(1);
	//char str[12] = "Inside clone2";
	//print2(str, strlen(str));
}

void test_read() {
	int tam_read = 5;
	char buffer[30];
	int err = read(0,buffer,tam_read);
	if (err >= 0) {
		print2("chars: ",7);
		print2(buffer,tam_read);
	}
	else print2("error",5);
}

int __attribute__ ((__section__(".text.main")))
   main(void)
{
   /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
   /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	
	//print2("Funca",5);
	//test_clone();
    //test_write();
    //exit();
    //test_read();
    test_fork();
    while(1) {
    	//exit();
    	//test_fork();
    }
    return 0;	
}
