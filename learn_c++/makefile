objects= 拷贝构造函数 类中读取数值 类中的函数 析构函数 继承和头文件 多个返回值

CC=g++
CFLAGS=
all: $(objects)
$(objects): %: %.cpp
				 $(CC) $(CFLAGS) $< -o $@
clean:
	  rm -f $(objects)
