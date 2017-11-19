declblock{
	int a;
}

codeblock{
	read a;
	l :
	println "as", a;
	a = a - 1;
	goto l if a > 0;
}

