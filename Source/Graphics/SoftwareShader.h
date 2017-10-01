//
// Created by genkinger on 10/1/17.
//

#ifndef ENGINE_SOFTWARESHADER_H
#define ENGINE_SOFTWARESHADER_H

#include <map>
#include "../Common.h"
using namespace M3D;

class SoftwareShader {

public:
    virtual void Execute() = 0; //acts as the main function
    void SetUniform(std::string name,float value);
    void SetUniform(std::string name,int value);
    void SetUniform(std::string name,bool value);

    void SetUniform(std::string name,Vec2f value);
    void SetUniform(std::string name,Vec3f value);
    void SetUniform(std::string name,Vec4f value);
    void SetUniform(std::string name,Mat4f value);

    auto GetUniform(std::string name);


private:

    std::map<std::string,int> mUniformInts;
    std::map<std::string,float> mUniformFloats;
    std::map<std::string,bool> mUniformBools;

    std::map<std::string,Vec2f> mUniformVec2fs;
    std::map<std::string,Vec3f> mUniformVec3fs;
    std::map<std::string,Vec4f> mUniformVec4fs;

    std::map<std::string,Mat4f> mUniformMat4fs;
};


#endif //ENGINE_SOFTWARESHADER_H
