SRC=main.cxx CSVReader.cxx utils.cxx ID3Tree.cxx Leaf.cxx Attribute.cxx TreeBuilder.cxx

all:
	g++ -g ${SRC} -o id3 -std=c++11

pizza:
	@echo "Give Elliott pizza, he worked hard on this project!"
