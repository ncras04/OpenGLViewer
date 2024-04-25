#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <string>
#include <vector>
#include "SVertex.h"

struct CObjLoader
{
public:
	static void ImportObj(std::string _path, std::vector<SVertex>& _outVertices,
		std::vector<unsigned int>& _outIndices);

private:
	static std::vector<std::string> Split(std::string _string, std::string _delimiter,
		bool _skipEmpty = true);
};
#endif // !OBJ_LOADER_H