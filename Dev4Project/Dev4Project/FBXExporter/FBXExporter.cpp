// FBXExporter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
//#include "resource.h"
#include <fbxsdk.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "DDSTextureLoader.h"

using namespace DirectX;
using namespace std;

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT3 Normal;
    XMFLOAT2 Tex;
};


struct ConstantBuffer
{
    XMMATRIX mWorld;
    XMMATRIX mView;
    XMMATRIX mProjection;
    XMFLOAT4 vLightDir[2];
    XMFLOAT4 vLightColor[2];
    XMFLOAT4 vOutputColor;
};

struct SimpleMesh
{
    vector<SimpleVertex> vertexList;
    vector<int> indicesList;
};

// Global simpleMesh
SimpleMesh simpleMesh;

// funtime random normal
#define RAND_NORMAL XMFLOAT3(rand()/float(RAND_MAX),rand()/float(RAND_MAX),rand()/float(RAND_MAX))

void ProcessFbxMesh(FbxNode* Node);
void Compactify(vector<SimpleVertex>* _expanded, vector<SimpleVertex>* _compacted, vector<int>* _index);
void SaveMesh(const char* meshFileName, SimpleMesh& mesh);
vector<XMFLOAT2> LoadUVInformation(FbxMesh* pMesh);

int main()
{
    // Change the following filename to a suitable filename value.
    const char* lFilename = "../Assets/WaterP.fbx";

    // Initialize the SDK manager. This object handles memory management.
    FbxManager* lSdkManager = FbxManager::Create();

    // Create the IO settings object.
    FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Create an importer using the SDK manager.
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // Use the first argument as the filename for the importer.
    if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings())) {
        printf("Call to FbxImporter::Initialize() failed.\n");
        printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
        exit(-1);
    }

    // Create a new scene so that it can be populated by the imported file.
    FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

    // Import the contents of the file into the scene.
    lImporter->Import(lScene);

    // The file is imported, so get rid of the importer.
    lImporter->Destroy();

    ProcessFbxMesh(lScene->GetRootNode());
    SaveMesh("../Assets/WaterP.mesh", simpleMesh);
}

void ProcessFbxMesh(FbxNode* Node)
{
    //FBX Mesh stuff
    int childrenCount = Node->GetChildCount();

    cout << "\nName:" << Node->GetName();

    for (int i = 0; i < childrenCount; i++)
    {
        FbxNode* childNode = Node->GetChild(i);
        FbxMesh* mesh = childNode->GetMesh();
        if (mesh != NULL)
        {
            cout << "\nMesh:" << childNode->GetName();

            // Get index count from mesh
            int numVertices = mesh->GetControlPointsCount();
            cout << "\nVertex Count:" << numVertices;

            // Resize the vertex vector to size of this mesh
            simpleMesh.vertexList.resize(numVertices);

            float maxSize = 0;

            for (int i = 0; i < numVertices; i++)
            {
                FbxVector4 vert = mesh->GetControlPointAt(i);
                if (vert.mData[0] > maxSize)
                    maxSize = vert.mData[0];

                if (vert.mData[1] > maxSize)
                    maxSize = vert.mData[1];

                if (vert.mData[2] > maxSize)
                    maxSize = vert.mData[2];
            }

            maxSize /= 4;

            maxSize = roundf(maxSize);

            //================= Process Vertices ===============
            for (int j = 0; j < numVertices; j++)
            {
                FbxVector4 vert = mesh->GetControlPointAt(j);
                simpleMesh.vertexList[j].Pos.x = (float)vert.mData[0] / maxSize;
                simpleMesh.vertexList[j].Pos.y = (float)vert.mData[1] / maxSize;
                simpleMesh.vertexList[j].Pos.z = (float)vert.mData[2] / maxSize;
                // Generate random normal for first attempt at getting to render
                //simpleMesh.vertexList[j].Normal = RAND_NORMAL;
            }

            int numIndices = mesh->GetPolygonVertexCount();
            cout << "\nIndice Count:" << numIndices;

            // No need to allocate int array, FBX does for us
            int* indices = mesh->GetPolygonVertices();

            // Fill indiceList
            simpleMesh.indicesList.resize(numIndices);
            memcpy(simpleMesh.indicesList.data(), indices, numIndices * sizeof(int));

            // Get the Normals array from the mesh
            FbxArray<FbxVector4> normalsVec;
            mesh->GetPolygonVertexNormals(normalsVec);
            cout << "\nNormalVec Count:" << normalsVec.Size();

            // Declare a new array for the second vertex array
            // Note the size is numIndices not numVertices
            vector<SimpleVertex> vertexListExpanded;
            vector<SimpleVertex> vertexList;
            vertexListExpanded.resize(numIndices);

            // align (expand) vertex array and set the normals
            for (int j = 0; j < numIndices; j++)
            {
                vertexListExpanded[j].Pos = simpleMesh.vertexList[indices[j]].Pos;
                vertexListExpanded[j].Normal.x = normalsVec[j].mData[0];
                vertexListExpanded[j].Normal.y = normalsVec[j].mData[1];
                vertexListExpanded[j].Normal.z = normalsVec[j].mData[2];
            }

            vector<XMFLOAT2>UVValues = LoadUVInformation(mesh);

            for (int i = 0; i < UVValues.size(); i++)
            {
                vertexListExpanded[i].Tex.x = UVValues[i].x;
                vertexListExpanded[i].Tex.y = UVValues[i].y;
            }

            // make new indices to match the new vertex(2) array
            vector<int> indicesList;
            /*indicesList.resize(numIndices);
            for (int j = 0; j < numIndices; j++)
            {
                indicesList[j] = j;
            }*/

            Compactify(&vertexListExpanded, &vertexList, &indicesList);

            // copy working data to the global SimpleMesh
            simpleMesh.indicesList.assign(indicesList.begin(), indicesList.end());
            simpleMesh.vertexList.assign(vertexList.begin(), vertexList.end());

            //================= Texture ========================================

            int materialCount = childNode->GetSrcObjectCount<FbxSurfaceMaterial>();

            for (int index = 0; index < materialCount; index++)
            {
                FbxSurfaceMaterial* material = (FbxSurfaceMaterial*)childNode->GetSrcObject<FbxSurfaceMaterial>(index);

                if (material != NULL)
                {
                    cout << "\nmaterial: " << material->GetName() << std::endl;
                    // This only gets the material of type sDiffuse, you probably need to traverse all Standard Material Property by its name to get all possible textures.
                    FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

                    // Check if it's layeredtextures
                    int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

                    if (layeredTextureCount > 0)
                    {
                        for (int j = 0; j < layeredTextureCount; j++)
                        {
                            FbxLayeredTexture* layered_texture = FbxCast<FbxLayeredTexture>(prop.GetSrcObject<FbxLayeredTexture>(j));
                            int lcount = layered_texture->GetSrcObjectCount<FbxTexture>();

                            for (int k = 0; k < lcount; k++)
                            {
                                FbxFileTexture* texture = FbxCast<FbxFileTexture>(layered_texture->GetSrcObject<FbxTexture>(k));
                                // Then, you can get all the properties of the texture, include its name
                                const char* textureName = texture->GetFileName();
                                cout << textureName;
                            }
                        }
                    }
                    else
                    {
                        // Directly get textures
                        int textureCount = prop.GetSrcObjectCount<FbxTexture>();
                        for (int j = 0; j < textureCount; j++)
                        {
                            FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxTexture>(j));
                            // Then, you can get all the properties of the texture, include its name
                            const char* textureName = texture->GetFileName();
                            cout << textureName;

                            FbxProperty p = texture->RootProperty.Find("Filename");
                            cout << p.Get<FbxString>() << std::endl;

                        }
                    }
                }
            }
        }
    }
}

void Compactify(vector<SimpleVertex>* _expanded, vector<SimpleVertex>* _compacted, vector<int>* _index)
{
    bool match = false;
    double epsilon = 0.1;
    for (int i = 0; i < _expanded->size(); i++)
    {
        for (int j = 0; j < _compacted->size(); j++)
        {
            if (abs(_expanded->at(i).Pos.x - _compacted->at(j).Pos.x) <= epsilon &&
                abs(_expanded->at(i).Pos.y - _compacted->at(j).Pos.y) <= epsilon &&
                abs(_expanded->at(i).Pos.z - _compacted->at(j).Pos.z) <= epsilon &&
                abs(_expanded->at(i).Normal.x - _compacted->at(j).Normal.x) <= epsilon &&
                abs(_expanded->at(i).Normal.y - _compacted->at(j).Normal.y) <= epsilon &&
                abs(_expanded->at(i).Normal.z - _compacted->at(j).Normal.z) <= epsilon &&
                abs(_expanded->at(i).Tex.x - _compacted->at(j).Tex.x) <= epsilon &&
                abs(_expanded->at(i).Tex.y - _compacted->at(j).Tex.y) <= epsilon)
            {
                _index->push_back(j);
                match = true;
            }

        }
        if (!match)
        {
            _index->push_back(_compacted->size());
            _compacted->push_back(_expanded->at(i));
        }
        match = false;
    }
}

void SaveMesh(const char* meshFileName, SimpleMesh& mesh)
{
    std::ofstream file(meshFileName, std::ios::trunc | std::ios::binary | std::ios::out);

    assert(file.is_open());

    uint32_t index_count = (uint32_t)mesh.indicesList.size();
    uint32_t vert_count = (uint32_t)mesh.vertexList.size();

    file.write((const char*)&index_count, sizeof(uint32_t));
    file.write((const char*)mesh.indicesList.data(), sizeof(uint32_t) * mesh.indicesList.size());
    file.write((const char*)&vert_count, sizeof(uint32_t));
    file.write((const char*)mesh.vertexList.data(), sizeof(SimpleVertex) * mesh.vertexList.size());
    file.close();
}

vector<XMFLOAT2> LoadUVInformation(FbxMesh* pMesh)
{
    //get all UV set names
    FbxStringList lUVSetNameList;
    pMesh->GetUVSetNames(lUVSetNameList);
    vector<XMFLOAT2> TextureUV;

    //iterating over all uv sets
    for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
    {
        //get lUVSetIndex-th uv set
        const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
        const FbxGeometryElementUV* lUVElement = pMesh->GetElementUV(lUVSetName);

        if (!lUVElement)
            continue;

        // only support mapping mode eByPolygonVertex and eByControlPoint
        if (lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
            lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
            return TextureUV;

        //index array, where holds the index referenced to the uv data
        const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
        const int lIndexCount = (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;

        //iterating through the data by polygon
        const int lPolyCount = pMesh->GetPolygonCount();

        if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
        {
            for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
            {
                // build the max index array that we need to pass into MakePoly
                const int lPolySize = pMesh->GetPolygonSize(lPolyIndex);
                for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
                {
                    FbxVector2 lUVValue;

                    //get the index of the current vertex in control points array
                    int lPolyVertIndex = pMesh->GetPolygonVertex(lPolyIndex, lVertIndex);

                    //the UV index depends on the reference mode
                    int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;

                    lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

                    //User TODO:
                    //Print out the value of UV(lUVValue) or log it to a file
                }
            }
        }
        else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
        {
            int lPolyIndexCounter = 0;
            for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
            {
                // build the max index array that we need to pass into MakePoly
                const int lPolySize = pMesh->GetPolygonSize(lPolyIndex);
                for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
                {
                    if (lPolyIndexCounter < lIndexCount)
                    {
                        FbxVector2 lUVValue;

                        //the UV index depends on the reference mode
                        int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;

                        lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

                        //User TODO:
                        //Print out the value of UV(lUVValue) or log it to a file
                        XMFLOAT2 temp;
                        temp.x = lUVValue.mData[0];
                        temp.y = lUVValue.mData[1];
                        TextureUV.push_back(temp);
                        lPolyIndexCounter++;
                    }
                }
            }
        }
    }
    return TextureUV;
}