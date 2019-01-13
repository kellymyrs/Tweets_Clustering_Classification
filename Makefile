make:
	g++  -o recommendation -std=c++11 -g3 main.cpp utils.cpp Hash_Function.cpp G.cpp Cosine_G.cpp Cosine_Hash_Function.cpp Hashtable.cpp Cosine_Hashtable.cpp Lsh_Hashtable.cpp Cosine_Lsh_Hashtable.cpp


clean:
	rm -rf recommendation *.o
