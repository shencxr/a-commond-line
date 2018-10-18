

obj += cmd.c main.c

console:$(obj)
	gcc $(obj) -o $@


clean:
	rm -rf console backup.txt
