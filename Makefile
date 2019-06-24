include /usr/local/etc/PcapPlusPlus.mk

# All Target
all:
	g++ $(PCAPPP_INCLUDES) -c -o final.o final.cpp
	g++ $(PCAPPP_LIBS_DIR) -static-libstdc++ -o Practice final.o $(PCAPPP_LIBS)

# Clean Target
clean:
	rm main.o
	rm Tutorial-HelloWorld

