objects= 拷贝构造函数 类中读取数值 类中的函数 

CC=g++
CFLAGS=
all: $(objects)
$(objects): %: %.cpp
				 $(CC) $(CFLAGS) $< -o $@
clean:
	  rm -f $(objects)
