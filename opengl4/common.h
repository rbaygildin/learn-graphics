#ifndef OPENGL2_COMMON_H
#define OPENGL2_COMMON_H


#include <ctime>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <boost/log/trivial.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

using namespace std;

#define constructors
#define funcs
#define fields


#define FOR(q, n) for(int q=0;q<n;q++)
#define SFOR(q, s, e) for(int q=s;q<=e;q++)
#define RFOR(q, n) for(int q=n;q>=0;q--)
#define RSFOR(q, s, e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()

typedef unsigned char BYTE;
typedef GLuint UINT;
#define FALSE GL_FALSE
#define TRUE GL_TRUE

#define COMMA ,
#define VERTEX(POINT) POINT.x COMMA POINT.y COMMA POINT.z

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0F, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define YELLOW 0.0f, 1.0f, 1.0f
#define DARK_GRAY 0.2f, 0.2f, 0.2f
#define LIGHT_GRAY 0.4f, 0.4f, 0.4f
#define PINK 1.0f, 0.25f, 0.56f

#define D2R(DEGREE) (DEGREE * M_PI / 180)

class POINT{
public:
    int x, y;
};

#endif //OPENGL2_COMMON_H
