#ifndef ENTITY_H
#define ENTITY_H
#include <QVector3D>
#include <vector>
#include <QMatrix4x4>
#include <QGLFunctions>
#include <QGLShaderProgram>
#include <functional>
#include "geometry/mesh.h"
#include "render/meshdrawcommand.h"
#include "shader/shaderpoll.h"
#include "base/camera.h"
#include "material/material.h"
#include "base/bonedata.h"
#include "base/boneinfo.h"
#include "base/ogldev_math_3d.h"
#include "external/include/assimp/scene.h"
#include "external/include/assimp/Importer.hpp"
#include "external/include/assimp/postprocess.h"
#include "base/node.h"

class Entity : public Node
{
	
}