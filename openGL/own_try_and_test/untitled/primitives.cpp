#include "primitives.h"


Geometry *newAxesGeometry()
{
    Geometry* geometry = new Geometry();
    {
        geometry->setPrimitiveMode(GL_LINES);
        glm::vec3 verts[] = { {0,0,0}, {1.0,0,0}, {0,0,0}, {0,1.0,0}, {0,0,0}, {0,0,1.0} };
        glm::vec3 colors[] = { {1,0,0}, {1,0,0},  {0,1,0}, {0,1,0},   {0,0,1}, {0,0,1} };
        geometry->setVertices((int)Attributes::position, verts, 6);
        geometry->setAttribute((int)Attributes::color, colors, 6);
    }
    return geometry;
}

Geometry *newPlaneGeometry(glm::vec2 size, glm::vec3 color)
{
    Geometry* geometry = new Geometry();
    {
        geometry->setPrimitiveMode(GL_TRIANGLES);
        glm::vec3 verts[]  = { {-size.x,-size.y,0}, {-size.x,size.y,0}, {size.x,size.y,0}, {size.x,-size.y,0}};
        glm::vec3 colors[] = { color, color, color, color};
        uint indices[] = {0,1,2,2,3,0};
        geometry->setIndices(indices, 6);
        geometry->setVertices((int)Attributes::position, verts, 4);
        geometry->setAttribute((int)Attributes::color, colors, 4);
    }
    return geometry;
}

Geometry* newBoxGeometry(glm::vec3 size, glm::vec3 color)
{
    Geometry* geometry = new Geometry();
    geometry->setPrimitiveMode(GL_TRIANGLES);
    {
        int n = 24;
        glm::vec3 origin = {0.0, 0.0, 0.0};
        float w = size.x;
        float h = size.y;
        float d = size.z;

        std::vector<glm::vec3> pos(n);
        std::vector<glm::vec3> colors(n);
        std::vector<uint> indices(36);
        std::vector<glm::vec2> uv(36);

        int it=0;
        // sciana z = +1  //front
        pos[it++] = origin + glm::vec3{-w,  h, d};
        pos[it++] = origin + glm::vec3{-w, -h, d};
        pos[it++] = origin + glm::vec3{ w, -h, d};
        pos[it++] = origin + glm::vec3{ w,  h, d};

        // sciana x=+1   //right
        pos[it++] = origin + glm::vec3{w,  h, d};
        pos[it++] = origin + glm::vec3{w, -h, d};
        pos[it++] = origin + glm::vec3{w, -h, -d};
        pos[it++] = origin + glm::vec3{w,  h, -d};

        // sciana z=-1   //back
        pos[it++] = origin + glm::vec3{-w,  h, -d};
        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{ w, -h, -d};
        pos[it++] = origin + glm::vec3{ w,  h, -d};

        // sciana x=-1   //left
        pos[it++] = origin + glm::vec3{-w,  h, d};
        pos[it++] = origin + glm::vec3{-w, -h, d};
        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{-w,  h, -d};

        // sciana y=1  //top
        pos[it++] = origin + glm::vec3{-w, h, -d};
        pos[it++] = origin + glm::vec3{-w, h,  d};
        pos[it++] = origin + glm::vec3{ w, h,  d};
        pos[it++] = origin + glm::vec3{ w, h, -d};

        // sciana y=-1  //bottom
        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{-w, -h,  d};
        pos[it++] = origin + glm::vec3{ w, -h,  d};
        pos[it++] = origin + glm::vec3{ w, -h, -d};


// -----------------------------------------------------

//        it=0;
//        // sciana zfront
//        uv[it++] = glm::vec2{ 0.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 0.0f/3.0f, 1.0f/2.0f};


//        uv[it++] = glm::vec2{ 0.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};


//        // sciana xight
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};


//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 1.0f/2.0f};

//        // sciana zack
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};


//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 0.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 1.0f/2.0f};

////-------------------
//        // sciana zfront
//        uv[it++] = glm::vec2{ 0.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 0.0f/3.0f, 2.0f/2.0f};


//        uv[it++] = glm::vec2{ 0.0f/3.0f, 2.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 2.0f/2.0f};


//        // sciana xight
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 2.0f/2.0f};


//        uv[it++] = glm::vec2{ 1.0f/3.0f, 2.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f,2.0f/2.0f};

//        // sciana zack
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 1.0f/3.0f, 2.0f/2.0f};


//        uv[it++] = glm::vec2{ 1.0f/3.0f, 2.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 1.0f/2.0f};
//        uv[it++] = glm::vec2{ 2.0f/3.0f, 2.0f/2.0f};


//        float i_ = 2.0f;
//        float j_= 3.0f;
//        for(float i = 0.0f; i < i_; i += 1)
//        {
//            for(float j = 0.0f; j < j_; j += 1){

//                uv.push_back( glm::vec2{j/j_,i/i_});
//                uv.push_back( glm::vec2{(j+1)/j_,i/i_});
//                uv.push_back( glm::vec2{j/j_,(i+1)/i_});

//                uv.push_back( glm::vec2{(j+1)/j_,i/i_});
//                uv.push_back( glm::vec2{j/j_,(i+1)/i_});
//                uv.push_back( glm::vec2{(j+1)/j_,(i+1)/i_});

//            }
//        }


        for(int i=0; i<n; i++)
            colors[i] = color;
        geometry->setVertices((int)Attributes::position, pos.data(), n);
        geometry->setAttribute((int)Attributes::color, colors.data(), n);
//        geometry->setAttribute((int)Attributes::uv1,uv.data(),36);

        it=0;
        indices[it++] = 0;    indices[it++] = 1;    indices[it++] = 2;    indices[it++] = 0;    indices[it++] = 2;    indices[it++] = 3;
        indices[it++] = 4;    indices[it++] = 5;    indices[it++] = 6;    indices[it++] = 4;    indices[it++] = 6;    indices[it++] = 7;
        indices[it++] = 8;    indices[it++] = 11;   indices[it++] = 10;   indices[it++] = 8;    indices[it++] = 10;   indices[it++] = 9;
        indices[it++] = 12;   indices[it++] = 15;   indices[it++] = 14;   indices[it++] = 12;   indices[it++] = 14;   indices[it++] = 13;
        indices[it++] = 16;   indices[it++] = 17;   indices[it++] = 18;   indices[it++] = 16;   indices[it++] = 18;   indices[it++] = 19;
        indices[it++] = 20;   indices[it++] = 23;   indices[it++] = 22;   indices[it++] = 20;   indices[it++] = 22;   indices[it++] = 21;


        geometry->setIndices(indices.data(), indices.size());
    }

    return geometry;
}





Geometry* newBoxLineGeometry(glm::vec3 size){
    Geometry* geometry = new Geometry();
    geometry->setPrimitiveMode(GL_TRIANGLES);

    {
        geometry->setPrimitiveMode(GL_LINES);

        int n = 24;
        glm::vec3 origin = {0.0, 0.0, 0.0};
        float w = size.x;
        float h = size.y;
        float d = size.z;

        std::vector<glm::vec3> pos(n);
        std::vector<glm::vec3> colors(n);
        std::vector<uint> indices(36);
        std::vector<glm::vec2> uv(36);

        int it=0;
        pos[it++] = origin + glm::vec3{w,  h, d};
        pos[it++] = origin + glm::vec3{-w, h, d};
        pos[it++] = origin + glm::vec3{-w, h, d};
        pos[it++] = origin + glm::vec3{-w,  h, -d};
        pos[it++] = origin + glm::vec3{-w,  h, -d};
        pos[it++] = origin + glm::vec3{w,  h, -d};
        pos[it++] = origin + glm::vec3{w,  h, -d};
        pos[it++] = origin + glm::vec3{w,  h, d};
        pos[it++] = origin + glm::vec3{-w, h, d};
        pos[it++] = origin + glm::vec3{-w,  -h, d};
        pos[it++] = origin + glm::vec3{-w,  -h, d};
        pos[it++] = origin + glm::vec3{-w,  -h, -d};
        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{-w,  h, -d};
        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{w,  -h, -d};
        pos[it++] = origin + glm::vec3{w,  -h, -d};
        pos[it++] = origin + glm::vec3{w,  -h, d};
        pos[it++] = origin + glm::vec3{w, -h, d};
        pos[it++] = origin + glm::vec3{-w,  -h, d};
        pos[it++] = origin + glm::vec3{w, -h, d};
        pos[it++] = origin + glm::vec3{w,  h, d};
        pos[it++] = origin + glm::vec3{w, -h, -d};
        pos[it++] = origin + glm::vec3{w,  h, -d};




        for(int i = 0; i < n; i++){
            colors.push_back({1,1,0});
        }

        geometry->setVertices((int)Attributes::position, pos.data(), 24);
        geometry->setAttribute((int)Attributes::color, colors.data(), 24);
    }
    return geometry;

}

Geometry* create_pyramid(glm::vec3 size, glm::vec3 color)
{
    Geometry* geometry = new Geometry();
    geometry->setPrimitiveMode(GL_TRIANGLES);
    {
        int n = 16;
        glm::vec3 origin = {0.0, 0.0, 0.0};
        float w = size.x;
        float h = size.y;
        float d = size.z;

        std::vector<glm::vec3> pos(n);
        std::vector<glm::vec3> colors(n);
        std::vector<uint> indices(36);

        int it=0;

        // sciana y=-1  //bottom
        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{-w, -h,  d};
        pos[it++] = origin + glm::vec3{ w, -h,  d};
        pos[it++] = origin + glm::vec3{ w, -h, -d};



        // sciana z = +1  //front
        pos[it++] = origin + glm::vec3{-w, -h, d};
        pos[it++] = origin + glm::vec3{ w, -h, d};
        pos[it++] = origin + glm::vec3{ w/2.0f,  h/2.0f, d/2.0f};

        // sciana x=+1   //right
        pos[it++] = origin + glm::vec3{w, -h, d};
        pos[it++] = origin + glm::vec3{w, -h, -d};
        pos[it++] = origin + glm::vec3{ w/2.0f,  h/2.0f, d/2.0f};


        // sciana z=-1   //back

        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{ w, -h, -d};
        pos[it++] = origin + glm::vec3{ w/2.0f,  h/2.0f, d/2.0f};


        // sciana x=-1   //left

        pos[it++] = origin + glm::vec3{-w, -h, d};
        pos[it++] = origin + glm::vec3{-w, -h, -d};
        pos[it++] = origin + glm::vec3{ w/2.0f,  h/2.0f, d/2.0f};

        for(int i=0; i<n; i++)
            colors[i] = color;
        geometry->setVertices((int)Attributes::position, pos.data(), n);
        geometry->setAttribute((int)Attributes::color, colors.data(), n);

        it=0;
        indices[it++] = 0;    indices[it++] = 1;    indices[it++] = 2;    indices[it++] = 0;    indices[it++] = 2;    indices[it++] = 3;
        indices[it++] = 4;    indices[it++] = 5;    indices[it++] = 6;    indices[it++] = 4;    indices[it++] = 6;    indices[it++] = 7;
        indices[it++] = 8;    indices[it++] = 11;   indices[it++] = 10;   indices[it++] = 8;    indices[it++] = 10;   indices[it++] = 9;
        indices[it++] = 12;   indices[it++] = 15;   indices[it++] = 14;   indices[it++] = 12;   indices[it++] = 14;   indices[it++] = 13;
        indices[it++] = 16;

        geometry->setIndices(indices.data(), indices.size());
    }
    return geometry;
}




Geometry* newSphereGeometry(glm::vec3 size, glm::vec3 color, float radius, int sectorCount, int stackCount)
{
    Geometry* geometry = new Geometry();
    geometry->setPrimitiveMode(GL_TRIANGLES);
    {
        glm::vec3 origin = {0.0, 0.0, 0.0};

        std::vector<glm::vec3> points;
        std::vector<glm::vec3> pos;
        std::vector<glm::vec2> normals;
        std::vector<glm::vec3> colors;
        std::vector<glm::vec2> uv;
        std::vector<uint> indices(36);

        std::vector<float> vertices, texCoords;
        std::vector<float>().swap(vertices);
        std::vector<glm::vec2>().swap(normals);
        std::vector<float>().swap(texCoords);
        std::vector<glm::vec2>().swap(uv);

        float x, y, z, xy;                              // vertex position
        float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
        float s, t;                                     // vertex texCoord

        float sectorStep = 2 * M_PI / sectorCount;
        float stackStep = M_PI / stackCount;
        float sectorAngle, stackAngle;

        for(int i = 0; i <= stackCount; ++i)
        {
            stackAngle = M_PI / 2 - i * stackStep;
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for(int j = 0; j <= sectorCount; ++j)
            {
                sectorAngle = j * sectorStep;           // starting from 0 to 2pia

                // vertex position (x, y, z)
                x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

               points.push_back({x,y,z});
               uv.push_back({x,y});
// uv push back
                // normalized vertex normal (nx, ny, nz)
                nx = x * lengthInv;
                ny = y * lengthInv;
//                nz = z * lengthInv;

                normals.push_back({nx,ny});
            }
        }


        // generate CCW index list of sphere triangles
        // k1--k1+1
        // |  / |
        // | /  |
        // k2--k2+1

        int k1, k2;
        for(int i = 0; i < stackCount; ++i)
        {
            k1 = i * (sectorCount + 1);
            k2 = k1 + sectorCount + 1;

            for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
                if(i != 0)
                {
                    pos.push_back(points[k1] + origin);
                    pos.push_back(points[k2] + origin);
                    pos.push_back(points[k1 + 1] + origin);

//                    uv.push_back(normals[k1]);
//                    uv.push_back(normals[k2]);
//                    uv.push_back(normals[k1 + 1]);



                }

                // k1+1 => k2 => k2+1
                if(i != (stackCount-1))
                {
                    pos.push_back(points[k1 + 1] + origin);
                    pos.push_back(points[k2] + origin);
                    pos.push_back(points[k2 + 1] + origin);

//                    uv.push_back(normals[k1 + 1]);
//                    uv.push_back(normals[k2]);
//                    uv.push_back(normals[k2 + 1]);
                }
            }
        }

        int n = pos.size();


        // --------------------

        for(int i=0; i<n; i++)
            colors.push_back(color);
        geometry->setVertices((int)Attributes::position, pos.data(), n);
        geometry->setAttribute((int)Attributes::color, colors.data(), n);
//        geometry->setAttribute((int)Attributes::uv1,uv.data(),uv.size()); // и заполнить эту таблицу


        // тпе же ьак и тут

//        for (int i = 0; i < n; i++){
//            indices.push_back(i);
//        }

//        geometry->setIndices(indices.data(), indices.size());
    }

    return geometry;
}


Geometry *newSphereLineGeometry(glm::vec3 size, glm::vec3 color, float radius, int sectorCount, int stackCount){
    Geometry* geometry = new Geometry();
    geometry->setPrimitiveMode(GL_LINES);
    {
        glm::vec3 origin = {0.0, 0.0, 0.0};

        std::vector<glm::vec3> points;
        std::vector<glm::vec3> pos;
        std::vector<glm::vec2> normals;
        std::vector<glm::vec3> colors;
        std::vector<glm::vec2> uv;
        std::vector<uint> indices(36);

        std::vector<float> vertices, texCoords;
        std::vector<float>().swap(vertices);
        std::vector<glm::vec2>().swap(normals);
        std::vector<float>().swap(texCoords);
        std::vector<glm::vec2>().swap(uv);

        float x, y, z, xy;                              // vertex position
        float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
        float s, t;                                     // vertex texCoord

        float sectorStep = 2 * M_PI / sectorCount;
        float stackStep = M_PI / stackCount;
        float sectorAngle, stackAngle;

        for(int i = 0; i <= stackCount; ++i)
        {
            stackAngle = M_PI / 2 - i * stackStep;
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for(int j = 0; j <= sectorCount; ++j)
            {
                sectorAngle = j * sectorStep;           // starting from 0 to 2pia
                x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

               points.push_back({x,y,z});
               uv.push_back({x,y});
            }
        }

        int k1, k2;
        for(int i = 0; i < stackCount; ++i)
        {
            k1 = i * (sectorCount + 1);
            k2 = k1 + sectorCount + 1;

            for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
                if(i != 0)
                {
                    pos.push_back(points[k1] + origin);
                    pos.push_back(points[k2] + origin);
                    pos.push_back(points[k1 + 1] + origin);
                }

                // k1+1 => k2 => k2+1
                if(i != (stackCount-1))
                {
                    pos.push_back(points[k1 + 1] + origin);
                    pos.push_back(points[k2] + origin);
                    pos.push_back(points[k2 + 1] + origin);
                }
            }
        }

        int n = pos.size();


        // --------------------

        for(int i=0; i<n; i++)
            colors.push_back(color);
        geometry->setVertices((int)Attributes::position, pos.data(), n);
        geometry->setAttribute((int)Attributes::color, colors.data(), n);

    }

    return geometry;
}
