#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glut.h>

class OBJMODEL {
    private:
        class Face {
          public:
            int edge;
            int *vertices;
            int normal;
            unsigned char color;

            Face(int edge, int *vertices, unsigned char inputcolor, int normal = -1) {
                this->edge = edge;
                this->vertices = vertices;
                this->normal = normal;
                color = inputcolor;
            }
        };

        std::vector <float*> vertices;
        std::vector <float*> texcoords;
        std::vector <float*> normals;
        std::vector <Face> faces;
        GLuint list;

    public:
        void load(const char*, char);
        void draw();
};

#endif // OBJMODEL_H
