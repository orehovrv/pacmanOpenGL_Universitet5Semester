#include "OBJMODEL.h"

void OBJMODEL::load(const char *filename, char model) {
    char tempstr[60];
    FILE *file;

    if((file = fopen(filename, "r")) == NULL) {
        printf("Cannot load model %s\n", filename);
        return;
    }

    float a, b, c;
    int v0, v1, v2, t0, t1, t2, n;
    int *v;

    while(fgets(tempstr, 60, file) != NULL) {
        if (tempstr[0] == 'v') {
            if (tempstr[1] == ' ') {
                sscanf(tempstr, "v %f %f %f", &a, &b, &c);
                vertices.push_back(new float[3]{a, b, c});
            } else if (tempstr[1] == 't') {
                sscanf(tempstr, "vt %f %f", &a, &b);
                texcoords.push_back(new float[2]{a, b});
            } else {
                sscanf(tempstr, "vn %f %f %f", &a, &b, &c);
                normals.push_back(new float[3]{a, b, c});
            }
        } else if (tempstr[0] == 'f') {
            sscanf(tempstr, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
            v = new int[3]{v0 - 1, v1 - 1, v2 - 1};
            faces.push_back(Face(3, v, t0, n - 1));
        }
    }

    fclose(file);

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
        for(int i = 0; i < faces.size(); i++) {
            Face face(faces[i]);

            if (face.normal != -1) {
                glNormal3fv(normals[face.normal]);
            } else {
                glDisable(GL_LIGHTING);
            }

            glBegin(GL_TRIANGLES);
                for (int i = 0; i < face.edge; i++) {
                    switch (model) { //выбор цвета грани
                        case 'c':
                            switch(face.color) {
                                case 1:
                                    glColor3f(237./255, 28./255, 36./255);
                                    break;

                                case 2:
                                    glColor3f(129./255, 81./255, 54./255);
                                    break;

                                default:
                                    glColor3f(237./255, 28./255, 36./255);
                                    break;
                            }
                            break;

                        case 'n':
                            glColor3f(1, 1, 0);
                            break;

                        case 'm':
                            switch(face.color) {
                                case 1:
                                    glColor3f(0, 0, 1);
                                    break;

                                case 2:
                                    glColor3f(0.5, 0.5, 0.5);
                                    break;

                                default:
                                    glColor3f(0.5, 0.5, 0.5);
                                    break;
                            }
                            break;

                        case 't':
                            switch(face.color) {
                                case 1:
                                    glColor3f(1, 1, 0);
                                    break;

                                case 2:
                                    glColor3f(1, 1, 1);
                                    break;

                                case 3:
                                    glColor3f(0, 0, 0);
                                    break;
                            }
                            break;

                        case 'y':
                        case 'u':
                        case 'i':
                        case 'o':
                        case 'p':
                            if(face.color == 2) glColor3f(1, 1, 1);
                            else if(face.color == 3) glColor3f(0, 0, 0);

                            switch(model) {
                                case 'y':
                                    if(face.color == 1) glColor3f(0.75, 0.75, 0.75);
                                    break;
                                case 'u':
                                    if(face.color == 1) glColor3f(1, 0, 0);
                                    break;

                                case 'i':
                                    if(face.color == 1) glColor3f(0.024, 0.204, 0.988);
                                    break;

                                case 'o':
                                    if(face.color == 1) glColor3f(0, 1, 1);
                                    break;

                                case 'p':
                                    if(face.color == 1) glColor3f(0.973, 0.725, 0.82);
                                    break;
                            }
                            break;

                        default:
                            glColor3f(1, 0, 0);
                            break;
                    }
                    glVertex3fv(vertices[face.vertices[i]]);
                }
            glEnd();

            if (face.normal == -1)
                glEnable(GL_LIGHTING);
        }
    glEndList();

    printf("Model: %s\n", filename);
    printf("Vertices: %d\n", vertices.size());
    printf("Texcoords: %d\n", texcoords.size());
    printf("Normals: %d\n", normals.size());
    printf("Faces: %d\n", faces.size());

    for (int i = 0; i < vertices.size(); i++) {
        delete vertices[i];
    }
    vertices.clear();

    for (int i = 0; i < texcoords.size(); i++) {
        delete texcoords[i];
    }
    texcoords.clear();

    for (int i = 0; i < normals.size(); i++) {
        delete normals[i];
    }
    normals.clear();
    faces.clear();

    printf("END READ FILE\n\n");
}

void OBJMODEL::draw() {
    glCallList(list);
}
