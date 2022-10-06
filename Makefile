
# Project file
NAME		=	trade-bot
# Project builds
DIR			= ./src/
SRCNAMES	= $(shell ls $(DIR) | grep -E ".+\.cpp")
SRC 		= $(addprefix $(DIR), $(SRCNAMES))
OBJ			= $(SRC:.cpp=.o)
INC 		= ./src/
BUILDDIR 	= ./build/
BUILDOBJS 	= $(addprefix $(BUILDDIR), $(SRCNAMES:.cpp=.o))
# Some flags

CC 			= g++
CFLAGS		= -Wall -Werror -Wextra

# Lib's paths

libcurl_dir=binacpp/lib/libcurl-7.56.0
libcurl_include=${libcurl_dir}/include
libcurl_lib=${libcurl_dir}/lib

jsoncpp_dir=binacpp/lib/jsoncpp-1.8.3
jsoncpp_include=${jsoncpp_dir}/include
jsoncpp_src=${jsoncpp_dir}/src


libwebsockets_dir=binacpp/lib/libwebsockets-2.4.0
libwebsockets_include=${libwebsockets_dir}/include
libwebsockets_lib=${libwebsockets_dir}/lib

libbinacpp_dir=binacpp/lib/libbinacpp
libbinacpp_include=${libbinacpp_dir}/include
libbinacpp_lib=${libbinacpp_dir}/lib

# Main rules
all: submodules copy $(BUILDDIR) $(NAME) shell

# Clone the submodule from binance repository
submodules:
	git submodule init
	git submodule update
# Copy src
copy:
	cp ./binacpp/example/run.template.sh ./src
	cp ./binacpp/example/cacert.pem ./src

# Object dir rule
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Object dir rule
$(BUILDDIR)%.o:$(DIR)%.cpp
	$(CC) -I$(libcurl_include) -I$(jsoncpp_include) \
	-I$(libwebsockets_include) -I$(libbinacpp_include) \
	-g -o $@ -c $<

# Create project file
$(NAME): $(BUILDOBJS)
	$(CC) $(CFLAGS) -L$(libcurl_lib) \
    -L$(libwebsockets_lib) \
    -L$(libbinacpp_lib) -lcurl -lcrypto -lwebsockets -lbinacpp -g -o $(NAME) $(BUILDOBJS)

# Rule for start shell-binance script

shell:
		cat ${DIR}run.template.sh  | sed s/%executable%/$@/ > ${NAME}.run.sh
		chmod 755 ${NAME}.run.sh

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -rf ${NAME}

make re: fclean all