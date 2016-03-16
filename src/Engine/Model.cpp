#include "Model.h"


#include <GL/glew.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool Model::Load()
{
    VertexIndices.clear();
    Vertices.clear();
    Normals.clear();
    UVs.clear();

	Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(Path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if(!pScene)
	{
		std::cout << "Error parsing " << Path << ": " << Importer.GetErrorString() << std::endl;
		return false;
    }

	for (unsigned int i = 0; i < pScene->mNumMeshes; i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Zero3D;
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

			Vertices.push_back(pPos->x);
			Vertices.push_back(pPos->y);
			Vertices.push_back(pPos->z);
			UVs.push_back(pTexCoord->x);
			UVs.push_back(pTexCoord->y);
			Normals.push_back(pNormal->x);
			Normals.push_back(pNormal->y);
			Normals.push_back(pNormal->z);
		}
		for (unsigned int i = 0 ; i < paiMesh->mNumFaces; i++)
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			VertexIndices.push_back(Face.mIndices[0]);
			VertexIndices.push_back(Face.mIndices[1]);
			VertexIndices.push_back(Face.mIndices[2]);
		}
	}

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &UVBO);
        glGenBuffers(1, &NBO);
        glGenBuffers(1, &IBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size()*sizeof(float), &Vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(ATTRIBUTE_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(ATTRIBUTE_VERTEX_POSITION);

        glBindBuffer(GL_ARRAY_BUFFER, UVBO);
        glBufferData(GL_ARRAY_BUFFER, UVs.size()*sizeof(float), &UVs[0], GL_STATIC_DRAW);
        glVertexAttribPointer(ATTRIBUTE_UV_COORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(ATTRIBUTE_UV_COORD);

        glBindBuffer(GL_ARRAY_BUFFER, NBO);
        glBufferData(GL_ARRAY_BUFFER, Normals.size()*sizeof(float), &Normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(ATTRIBUTE_NORMAL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexIndices.size()*sizeof(unsigned short), &VertexIndices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
    
    CalculateCollisionInfo();

    return true;
}

void Model::Destroy()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteBuffers(1, &UVBO);
    glDeleteBuffers(1, &NBO);
    glDeleteVertexArrays(1, &VAO);
}

void Model::CalculateCollisionInfo()
{
    if(!Vertices.empty())
    {
        bool bCalculateCentreOffset = true;
        bool bCalculateRadius = true;
        if(bCalculateCentreOffset)
        {
            glm::vec3 sum = glm::vec3(0, 0, 0);
            glm::vec3 count = glm::vec3(0, 0, 0);
            int i=0;
            for(float v : Vertices)
            {
                switch(i)
                {
                case 0:
                    sum.x += v;
                    count.x++;
                    break;
                case 1:
                    sum.y += v;
                    count.y++;
                    break;
                case 2:
                    sum.z += v;
                    count.z++;
                    break;
                }
                i++;
                if(i > 2)
                {
                    i = 0;
                }
            }
            CentreOffset = glm::vec3(sum.x/count.x,
                                     sum.y/count.y,
                                     sum.z/count.z);
        }
        if(bCalculateRadius)
        {
            float trad;
            float x, y, z; int i;
            for(float v : Vertices)
            {
                switch(i)
                {
                case 0:
                    x=v;
                    break;
                case 1:
                    y=v;
                    break;
                case 2:
                    z=v;
                    break;
                }
                i++;
                if(i > 2)
                {
                    float d = glm::length(glm::vec3(x,y,z) - CentreOffset);
                    if(d > trad)
                    {
                        trad = d;
                    }
                    i = 0;
                }
            }
            MaximumRadius = trad;
        }
    }
}

/*
bool Model::ParseModel(const std::string& filepath)
{
    VertexIndices.clear();
    NormalIndices.clear();
    UVIndices.clear();
    Vertices.clear();
    Normals.clear();
    UVs.clear();

    BoundFile = File(filepath);

    std::vector<std::string> Lines;
    StringHelper::Split(Lines, BoundFile.FileData, '\n');

    bool bNoUV = false, bNoNormal = false;

    for(unsigned int j=0; j<Lines.size(); j++)
    {
        std::vector<std::string> Subsections;
        StringHelper::Split(Subsections, Lines[j], ' ');
        if(Subsections.size() > 0)
        {
            std::string header = Subsections[0];
            if(header == "o")
            {
                ModelName = Subsections[1];
            }
            else if(header == "v")
            {
                if(Subsections.size()-1 != 3) continue;
                //Vertices.push_back(glm::vec3((float)atof(Subsections[1].c_str()), (float)atof(Subsections[2].c_str()), (float)atof(Subsections[3].c_str())));
                Vertices.push_back((float)atof(Subsections[1].c_str()));
                Vertices.push_back((float)atof(Subsections[2].c_str()));
                Vertices.push_back((float)atof(Subsections[3].c_str()));
            }
            else if(header == "vt")
            {
                if(Subsections.size()-1 != 2) continue;
                //UVs.push_back(glm::vec2((float)atof(Subsections[1].c_str()), (float)atof(Subsections[2].c_str())));
                UVs.push_back((float)atof(Subsections[1].c_str()));
                UVs.push_back((float)atof(Subsections[2].c_str()));
            }
            else if(header == "vn")
            {
                if(Subsections.size()-1 != 3) continue;
                //Normals.push_back(glm::vec3((float)atof(Subsections[1].c_str()), (float)atof(Subsections[2].c_str()), (float)atof(Subsections[3].c_str())));
                Normals.push_back((float)atof(Subsections[1].c_str()));
                Normals.push_back((float)atof(Subsections[2].c_str()));
                Normals.push_back((float)atof(Subsections[3].c_str()));
            }
            else if(header == "f")
            {
                if(Subsections.size()-1 != 3) continue;
                for(unsigned int i=1; i < Subsections.size(); i++)
                {
                    std::vector<std::string> vun;
                    StringHelper::Split(vun, Subsections[i], '/');
                    if(vun.size() != 3)
                        break;
                    int vi = atoi(vun[0].c_str())-1;
                    if(vi >= 0)
                    {
                        VertexIndices.push_back(vi);
                    }
                    else
                    {
                        std::cout << "ERROR: " << filepath << " Line: " << j+1 << " Index: " << vi << std::endl;
                    }
                    int ui = atoi(vun[1].c_str())-1;
                    if(ui >= 0)
                    {
                        UVIndices.push_back(ui);
                    }
                    else
                    {
                        bNoUV = true;
                    }

                    int ni = atoi(vun[2].c_str())-1;
                    if(ni >= 0)
                    {
                        NormalIndices.push_back(ni);
                    }
                    else
                    {
                        bNoNormal = true;
                    }
                }
            }
        }
    }

    // Convert UVIndices and UVs into pure UVs
    if(!bNoUV)
    {
        std::vector<float> PureUVs = {};
        for(auto& index : UVIndices)
        {
            PureUVs.push_back(UVs[index*2]);
            PureUVs.push_back(UVs[index*2+1]);
        }
        UVs = PureUVs;
    }


    // Convert Normals
    if(!bNoNormal)
    {
        std::vector<float> PureNormals = {};
        for(auto& index : NormalIndices)
        {
            PureNormals.push_back(Normals[index*3]);
            PureNormals.push_back(Normals[index*3+1]);
            PureNormals.push_back(Normals[index*3+2]);
        }
        Normals = PureNormals;
	}
    return true;
}
*/
