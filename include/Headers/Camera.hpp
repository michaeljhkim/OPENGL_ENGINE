// Camera.hpp
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <tiny_obj_loader.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
    public:
        Camera();
        glm::mat4 GetViewMatrix() const;

        void MouseLook(int mouseX, int mouseY);
        void MoveForward(float speed);
        void MoveBack(float speed);
        void MoveLeft(float speed);
        void MoveRight(float speed);

    private:
        glm::vec3 mEye; 
        glm::vec3 mViewDirection; 
        glm::vec3 mUpVector; 

        glm::vec2 mOldMousePosition; 
};

#endif