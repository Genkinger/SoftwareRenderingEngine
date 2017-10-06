//
// Created by genkinger on 10/2/17.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H


class Application {
public:
    virtual void Start() = 0;
protected:
    virtual void Run() = 0;
    virtual void Stop() = 0;

};


#endif //ENGINE_APPLICATION_H
