asst6: asst6.c some_heap.c
	gcc -o asst6.exe asst6.c some_heap.c

some_heap: some_heap.c some_heap.c
	gcc -o some_heap.exe some_heap.c

clean:
	rm asst6.exe some_heap.exe