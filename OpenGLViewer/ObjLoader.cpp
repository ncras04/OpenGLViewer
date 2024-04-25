
#include "ObjLoader.h"
#include <fstream>
#include <map>
#include "SVertex.h"
#include <glm/glm.hpp>

void CObjLoader::ImportObj(std::string _path,
	std::vector<SVertex>& _outVertices,
	std::vector<unsigned int>& _outIndices)
{
	std::ifstream infile(_path);

	std::vector<std::string> split;
	std::string line;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<std::string> faceStrings;
	std::vector<SVertex> vertices;
	std::map<std::string, short> indicesByString;
	std::vector<unsigned int> indices;

	while (std::getline(infile, line))
	{
		if (line.size() == 0)
			continue;
		if (line[0] == '#')
			continue;

		split = Split(line, " ");
		if (split.size() == 0)
			continue;
		if (split[0] == "v")
		{
			if (split.size() != 4)
				continue;

			positions.push_back({ std::stof(split[1]), std::stof(split[2]),
									std::stof(split[3]) });
		}
		else if (split[0] == "vn")
		{
			if (split.size() != 4)
				continue;

			normals.push_back({ std::stof(split[1]), std::stof(split[2]),
									std::stof(split[3]) });
		}
		else if (split[0] == "vt")
		{
			if (split.size() < 3)
				continue;

			uvs.push_back({ std::stof(split[1]), std::stof(split[2]) });
		}
		else if (split[0] == "f")
		{
			faceStrings.push_back(line);
		}
	}

	glm::vec3 position{ 0, 0, 0 };
	glm::vec3 normal{ 0, 0, 0 };
	glm::vec2 uv{ 0, 0 };
	std::vector<std::string> vertexStringSplit;
	for (std::string faceString : faceStrings)
	{
		position = { 0, 0, 0 };
		normal = { 0, 0, 0 };
		uv = { 0, 0 };
		split = Split(faceString, " ");
		if (indicesByString.find(split[1]) != indicesByString.end())
		{
			indices.push_back(indicesByString[split[1]]);
		}
		else
		{
			vertexStringSplit = Split(split[1], "/", false);

			for (int j = 0; j < vertexStringSplit.size(); j++)
			{
				if (vertexStringSplit[j].size() == 0)
					continue;
				if (j == 0)
				{
					// position
					position = positions[std::stoi(vertexStringSplit[j]) - 1];
				}
				if (j == 1)
				{
					// normal
					normal = normals[std::stoi(vertexStringSplit[j]) - 1];
				}
				if (j == 2)
				{
					// uv
					uv = uvs[std::stoi(vertexStringSplit[j]) - 1];
				}
			}

			SVertex vertex = { position, glm::vec4(1.0), normal, uv };
			vertices.push_back(vertex);
			indices.push_back(vertices.size() - 1);
			indicesByString.emplace(split[1], (short)vertices.size() - 1);
		}
		// f 1 2 3 4 5 6 7 8
		for (int i = 1; i < split.size() - 2; i++)
		{
			position = { 0, 0, 0 };
			normal = { 0, 0, 0 };
			uv = { 0, 0 };
			for (int j = 1; j < 3; j++)
			{
				if (indicesByString.find(split[j + i]) != indicesByString.end())
				{
					indices.push_back(indicesByString[split[i]]);
					continue;
				}
				vertexStringSplit = Split(split[j + i], "/");

				for (int j = 0; j < vertexStringSplit.size(); j++)
				{
					if (vertexStringSplit[j].size() == 0)
						continue;
					if (j == 0)
					{
						// position
						position = positions[std::stoi(vertexStringSplit[j]) - 1];
					}
					if (j == 1)
					{
						// uv
						uv = uvs[std::stoi(vertexStringSplit[j]) - 1];
					}
					if (j == 2)
					{
						// normal
						normal = normals[std::stoi(vertexStringSplit[j]) - 1];
					}
				}

				SVertex vertex = { position, glm::vec4(1.0), normal, uv };
				vertices.push_back(vertex);
				indices.push_back(vertices.size() - 1);
				indicesByString.emplace(split[j + i], (short)vertices.size() - 1);


				//f 1 2 3 4 5 6 7 9
			}
		}
	}

	_outVertices = vertices;
	_outIndices = indices;
}

std::vector<std::string> CObjLoader::Split(std::string _string,
	std::string _delimiter, bool _skipEmpty)
{
	std::vector<std::string> returnValue;
	int delimiterPos;
	int start = 0;
	bool isCutting = true;
	for (int i = 0; i < _string.size() + 1; i++)
	{
		// 1//2 = {1},{},{2}
		if (_string[i] == _delimiter[0] || i == _string.size())
		{
			delimiterPos = i;
			if (delimiterPos > start || !_skipEmpty)
				returnValue.push_back(_string.substr(start, delimiterPos - start));

			start = delimiterPos + 1;
		}
	}

	return returnValue;
}

